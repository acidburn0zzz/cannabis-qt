PRAGMA foreign_keys=OFF;

BEGIN TRANSACTION;

CREATE TABLE "Socis" ("Codi" INTEGER PRIMARY KEY, "DataAlta" TEXT NOT NULL, "DNI" TEXT NOT NULL, "Nom" TEXT NOT NULL, "Cognom1" TEXT, "Cognom2" TEXT, "Adreça" TEXT, "Telefon" TEXT, "CodiPostal" TEXT, "Poblacio" TEXT, "Email" TEXT, "Pagat" INTEGER NOT NULL);

CREATE TABLE "Cannabis" ("Id" INTEGER PRIMARY KEY AUTOINCREMENT, "CodiSoci" INTEGER NOT NULL, "Data" TEXT NOT NULL, "IdPot" INTEGER NOT NULL, "Grams" INTEGER NOT NULL, "Preu" REAL NOT NULL);

CREATE TABLE "Pots" ("Id" INTEGER PRIMARY KEY, "Grams" INTEGER NOT NULL);

CREATE TABLE "Altres" ("Id" INTEGER PRIMARY KEY AUTOINCREMENT, "Data" TEXT NOT NULL, "Diners" REAL NOT NULL);

# Insert test data to our database

INSERT INTO "Socis" ("Codi", "DataAlta", "DNI", "Nom", "Cognom1", "Cognom2", "Adreça", "Telefon", "CodiPostal", "Poblacio", "Email", "Pagat") VALUES (100, '25/03/2009', '11223344A', 'Joan', 'Perramon', 'Gràcia', 'Juvenal, 1', '937776655', '08201', 'Sabadell', 'joanperramon@gmail.com', 1);
INSERT INTO "Socis" ("Codi", "DataAlta", "DNI", "Nom", "Cognom1", "Cognom2", "Adreça", "Telefon", "CodiPostal", "Poblacio", "Email", "Pagat") VALUES (201, '21/04/2008', '23423423A', 'Xavi', 'Fernàndez', 'Jovè', 'Xin xan, 100, 2n 1a', '937776655', '08201', 'Sabadell', 'kasdas_iadf@hotmail.com', 0);
INSERT INTO "Socis" ("Codi", "DataAlta", "DNI", "Nom", "Cognom1", "Cognom2", "Adreça", "Telefon", "CodiPostal", "Poblacio", "Email", "Pagat") VALUES (202, '22/02/2004', '23423435B', 'Pere', 'Martínez', 'Garcia', 'Crta. Terrassa, 1023', '937776655', '08201', 'Sabadell', '1234lasdkf_alsd@gmail.com', 1);
INSERT INTO "Socis" ("Codi", "DataAlta", "DNI", "Nom", "Cognom1", "Cognom2", "Adreça", "Telefon", "CodiPostal", "Poblacio", "Email", "Pagat") VALUES (1002, '05/03/2006','X4578456Z', 'Marc', 'Palet', 'Castells', 'Gran Via de les Corts Catalanes, 2002, 2on 5a', '937776655', '08201', 'Badía del Vallès', 'mon@gmail.com', 1);

INSERT INTO "Cannabis" ("CodiSoci", "Data", "IdPot", "Grams", "Preu") VALUES (100, '10/07/2010', 1, 100, 25.30);
INSERT INTO "Cannabis" ("CodiSoci", "Data", "IdPot", "Grams", "Preu") VALUES (100, '23/12/2012', 2, 200, 55.30);
INSERT INTO "Cannabis" ("CodiSoci", "Data", "IdPot", "Grams", "Preu") VALUES (100, '12/11/2012', 3, 300, 45.30);
INSERT INTO "Cannabis" ("CodiSoci", "Data", "IdPot", "Grams", "Preu") VALUES (100, '22/06/2012', 4, 140, 75.30);
INSERT INTO "Cannabis" ("CodiSoci", "Data", "IdPot", "Grams", "Preu") VALUES (201, '12/05/2012', 2, 20, 55.30);
INSERT INTO "Cannabis" ("CodiSoci", "Data", "IdPot", "Grams", "Preu") VALUES (201, '11/04/2012', 3, 102, 24.30);
INSERT INTO "Cannabis" ("CodiSoci", "Data", "IdPot", "Grams", "Preu") VALUES (201, '12/03/2012', 2, 430, 5.30);
INSERT INTO "Cannabis" ("CodiSoci", "Data", "IdPot", "Grams", "Preu") VALUES (1002, '11/04/2012', 3, 252, 25.30);
INSERT INTO "Cannabis" ("CodiSoci", "Data", "IdPot", "Grams", "Preu") VALUES (1002, '13/08/2012', 2, 425, 25.30);
INSERT INTO "Cannabis" ("CodiSoci", "Data", "IdPot", "Grams", "Preu") VALUES (1002, '08/07/2012', 1, 164, 25.30);
INSERT INTO "Cannabis" ("CodiSoci", "Data", "IdPot", "Grams", "Preu") VALUES (1002, '01/03/2012', 1, 176, 25.30);
INSERT INTO "Cannabis" ("CodiSoci", "Data", "IdPot", "Grams", "Preu") VALUES (1002, '12/04/2012', 2, 432, 25.30);

INSERT INTO "Pots" ("Id", "Grams") VALUES (1, 1000);
INSERT INTO "Pots" ("Id", "Grams") VALUES (2, 1100);
INSERT INTO "Pots" ("Id", "Grams") VALUES (3, 800);
INSERT INTO "Pots" ("Id", "Grams") VALUES (4, 200);

INSERT INTO "Altres" ("Data", "Diners") VALUES ('21/02/2001', 302);
INSERT INTO "Altres" ("Data", "Diners") VALUES ('11/04/2011', 503);
INSERT INTO "Altres" ("Data", "Diners") VALUES ('06/05/2012', 205);
INSERT INTO "Altres" ("Data", "Diners") VALUES ('05/06/2012', 406);
INSERT INTO "Altres" ("Data", "Diners") VALUES ('04/03/2012', 500);
INSERT INTO "Altres" ("Data", "Diners") VALUES ('18/04/2011', 208);
INSERT INTO "Altres" ("Data", "Diners") VALUES ('02/06/2010', 100);

COMMIT;
