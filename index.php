<?php
require_once('config.inc');

if (!$db->tableExists('modules')) core::install();

$tpl = new template('templates');
$tpl->display('header.tpl');
core::run('gaderob');
get();
$tpl->display('middle.tpl');
core::run('gaderob','client');
get();
$tpl->display('footer.tpl');

?>
