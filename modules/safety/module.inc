<?php
/**
 *
 * Increased safety
 * 
 * PHP Version 5
 *
 * @category   Safety 
 * @copyright  2006 the zion framework
 * @link       http://stamp.se/
 * @author     Jonathan Svensson-Köhler <stamp@stamp.se>
 **/
 
class safety extends module {

    function __construct () {
        $this->setId(get_class($this));
        $this->setName('Safety');
        $this->setDescription('Secures all user input');
        $this->setVersion('0.1.0');
        $this->setRequiredCoreApi('1.0');
        $this->setRequiredModuleApi('1.0');
        $this->setMaintainer('Jonathan Svensson-Köhler <stamp@stamp.se>');
    }
    
    function init() {
        $_POST = $this->secure($_POST);
        
        //$this->check();
    }
    
    function secure($data) {
        return new variable($data);
    }
    
    function hash() {
        $_SESSION['hash'] = sha1(microtime(true));
        return $_SESSION['hash'];
    }
    
    function check() {
        if (!isset($_SESSION['hash']))
            return false;
            
        if (!isset($_POST) || (isset($_POST) && count($_POST) < 1))
            return false;
            
        if ($_POST['hash'] != $_SESSION['hash']) {
            $_POST = array();
            send(E_ERROR, 'SAFETY: Post w/o correct key killed!');
            return false;
        }
        
        return true;
    }

}

class variable extends ArrayObject
{
    private $var = array();

    function raw($key) {
        return $this[$key];
    }
    
    function sql($key) {
        return db::escapeStr($this[$key]);
    }

    function nohtml($key,$escape = true) {
        $filter = new InputFilter();
        if ($escape)
            return $filter->process(self::sql($key));
        return $filter->process($this[$key]);
    }

    function clean($key,$escape = true) {
        $tags = array('qoute','br','em','strong','h1','h2','h3','h4','h5','h6','b','i','a','ul','li');
        $attr = array('user','post','href');
        $filter = new InputFilter($tags,$attr);
        
        if ($escape)
            return $filter->process(self::sql($key));
        return $filter->process($this[$key]);
    
    } 

    function html($key,$escape = true) {
        if ($escape)
            return htmlspecialchars(self::sql($key));
        return htmlspecialchars($this[$key]);
    }

    function is_set($key) {
        return isset($this[$key]);
    }

    function numeric($key) {
        return is_numeric($this[$key]);
    }

    function isset_else($key, $else) {
        return isset($this[$key]) ? true : $else;
    }
}

?>
