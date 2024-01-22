<?php

class zaklad {
	protected $db; // pristup k DB

	//! HTTP route post-processor
	function afterroute() {
		//$f3->set('cesta','http://'.$_SERVER['SERVER_NAME']);// DODELAT! $f3
		// Render HTML layout
		echo Template::instance()->render('_layout.html');
		// echo View::instance()->render('layout.htm');
		$f3 = Base::instance();
		if (null !== $f3->get('SESSION.error'))
			$f3->clear('SESSION.error');
		if (null !== $f3->get('SESSION.ok'))
			$f3->clear('SESSION.ok');
	}

	//! Instantiate class
	function __construct() {
		$f3=Base::instance();
//		new Session();
		// Connect to the database
		$this->db = new DB\SQL($f3->get('db'));
		
		// Database creating
		if (file_exists('setup.sql')) {
			// Initialize database with default setup
			$this->db->exec(explode(';',$f3->read('setup.sql')));
			// Make default setup inaccessible
			rename('setup.sql','setup.$ql');
		}
	/*	// Use database-managed sessions
		new DB\SQL\Session($db);
		// Save frequently used variables
		$this->db=$db;
	*/
	}
	
	// test přihlášeného uživatele
	protected function test_logged() {
		$f3 = Base::instance();
		if (null == $f3->get('SESSION.userID')) {
			$f3->set('SESSION.error','Požadovanou akci smí provádět pouze přihlášený uživatel!');
			$f3->reroute('/');
		}
	}
		
	// vykreslení úvodní stránky
	function home(\Base $f3) {
		/* $classes=array('banán','jablko','hruška');
		$f3->set('classes',$classes);
		$pomocna = $f3->format('Page rendered in {0} msecs / Memory usage {1} Kibytes',round(1e3*(microtime(TRUE)-$TIME),2),round(memory_get_usage(TRUE)/1e3,1));
		$hashpw = password_hash('12358',PASSWORD_DEFAULT);
		$hashpw = '';
		$f3->set('statistiky',$hashpw.' '.$pomocna);

		$f3->set('subtitle','Úvodní stránka');
		$f3->set('content','home.htm');
        */
        //$hash = password_hash("kopretina", PASSWORD_DEFAULT);
		$f3->set('subtitle',"Úvodní stránka"); // $hash");
		$f3->set('content','home.html');
	}
	
}
