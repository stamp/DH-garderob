<?php

class gaderob extends module {
    
    function __construct() {
        $this->setId(get_class($this));
        $this->setName('Gaderob');
        $this->setDescription('DHs gaderob :D');
        $this->setVersion('0.1.0');
        $this->setRequiredCoreApi('1.0');
        $this->setRequiredModuleApi('1.0');
        $this->setDepends('safety');
        $this->setMaintainer('Jonathan Svensson-Köhler <stamp@stamp.se>');
    }

    function install() {
        $tables = array (
            'gaderob' => array(
                array(
                    'Field'   => 'id',
                    'Type'    => 'int(11)',
                    'Key'     => 'PRI',
                    'Extra'   => 'auto_increment'
                ),
                array(
                    'Field'   => 'ident',
                    'Type'    => 'int(10)'
                ),
                array(
                    'Field'   => 'position',
                    'Type'    => 'varchar(255)'
                ),
                array(
                    'Field'   => 'timestamp',
                    'Type'    => 'timestamp'
                )
            )
        );

        $this->installTables($tables);
        
        return parent::install();
    }

    function _run() {
    	echo 'Klar';
    }

    function client() {
	$this->display('client.tpl');
    }

    function _admin() {
    
    }
}

?>
