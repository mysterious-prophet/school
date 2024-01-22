<?php // konfigurační soubor pro připojení k databázovému systému MySQL

define('SERVER','localhost'); // místo localhost může být např. 'mysql.webzdarma.cz' nebo IP adresa (pozor: některé databázové servery NEpodporují připojení "z cizích" skriptů)!
define('USER','inta'); // nebo 'php' a podobně. Server INTA: 'inta'
define('PASS','intadata'); // nebo jiné heslo. Server INTA: 'intadata'

define('DB_NAME','studium2020'); // nebo jiné jméno databáze. Server INTA: 'inta_<usernameKOS>'

define('ZNAKOVA_SADA','utf8');
define('MOD_LADENI',0); // 1 ... ladíme (chceme vidět chyby), 0 ... ostrý provoz (s LOG-souborem)
define('LOG_SOUBOR','./log/cinnost.dat'); // jméno LOG-souboru (adresář vlastněný PHP => nastavte práva zápisu!)
