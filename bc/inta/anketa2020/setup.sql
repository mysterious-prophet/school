CREATE TABLE IF NOT EXISTS a_uzivatel (
    idu INTEGER NOT NULL,
    jmeno VARCHAR(25) NOT NULL,
    prijmeni VARCHAR(50) NOT NULL,
    login VARCHAR(25) NOT NULL,
    heslo VARCHAR(255) NOT NULL,
    PRIMARY KEY (idu),
    UNIQUE (login)
);
INSERT INTO a_uzivatel VALUES (
        1,
        'Dana',
        'Majerova',
        'admin',
        '$2y$10$TR4Oe94ubxFHasKCGTHawee8IEZ6bqaczs33thFO1.RL5DFkFb6R2'
); -- heslo je "kopretina" ... PHP: password_hash("kopretina", PASSWORD_DEFAULT)
CREATE TABLE IF NOT EXISTS a_otazka (
	idot INTEGER NOT NULL,
	textot VARCHAR(255) NOT NULL,
	datum_od TIMESTAMP NOT NULL,
	datum_do TIMESTAMP,
	tvurce INTEGER NOT NULL,
	PRIMARY KEY (idot),
	FOREIGN KEY (tvurce) REFERENCES a_uzivatel (idu) ON UPDATE CASCADE ON DELETE RESTRICT
);
CREATE TABLE IF NOT EXISTS a_odpoved (
	idotazky INTEGER NOT NULL,
	idodpo INTEGER NOT NULL,
	textodpo VARCHAR(255) NOT NULL,
	pocet_hlasu INTEGER NOT NULL DEFAULT 0,
	barva VARCHAR(6),
	PRIMARY KEY (idotazky,idodpo),
	FOREIGN KEY (idotazky) REFERENCES a_otazka (idot) ON UPDATE CASCADE ON DELETE RESTRICT
);
