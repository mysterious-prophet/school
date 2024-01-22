<?php

class uzivatel extends zaklad {

    public function beforeRoute(\Base $f3) {
        // kontroluje přihlášení
		if (!$f3->get('SESSION.userID')) {
            if ($f3->get('PATH') != '/login') {
                $f3->set('SESSION.error','Požadovanou akci smí provádět pouze přihlášený uživatel. Přihlaste se.');
                $f3->reroute('/login'); // přesměrování na přihl. formulář (metoda GET)
            }
        }
    }
	
	public function __construct() {
		parent::__construct();
		// print_r($this->db);
		//print_r(Base::instance());
		session_start();
	}


	public function login_form(\Base $f3) {
		$f3->set('subtitle','Přihlášení');
		$f3->set('content','login.html');
	}
	
	public function login_check(\Base $f3) {
        unset($_SESSION['userID']); // $f3->clear() není vhodné
		
		$user = $f3->get('POST.username');
		$row = $this->db->exec('SELECT idu,jmeno,prijmeni,heslo FROM a_uzivatel WHERE login=?',$user);
		if(count($row)==1 && password_verify($f3->get('POST.password'),$row[0]['heslo'])) {
            $_SESSION['userID'] = $row[0]['idu'];
            $_SESSION['name'] = $row[0]['jmeno'].' '.$row[0]['prijmeni'];
            $f3->reroute('/');
        }
        else {
//        $data = $row[0]['heslo'];
//        $odpo = (password_verify('kopretina','$2y$10$VDg2aOaKLzELb6pHo0ZYoOGr2DHiuyTD3EjIPIU4FsTOPO6CnyfUa'))?'ano':'ne';
            $_SESSION['error'] = "Špatné uživatelské jméno nebo heslo."; // ($data, $odpo).";
            $f3->reroute('/login');
        }
    }

    public function logout(\Base $f3) {
        $_SESSION = array();
        // smazat COOKIE!!!
        $f3->reroute('/');
    }

}
