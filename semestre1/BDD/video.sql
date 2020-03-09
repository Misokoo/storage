drop table if exists Location;
drop table if exists Realisation;
drop table if exists Joue;
drop table if exists Classification;
drop table if exists Stock;
drop table if exists Film ;
drop table if exists Categorie;
drop table if exists Distributeur;
drop table if exists Artiste;
drop table if exists Client;
drop table if exists Magasin;

create table Magasin
(
   numMagasin int primary key,
   Adresse varchar(100)     
);

create table Client
(
   numClient int primary key,
   Nom varchar(50)          ,
   Adresse varchar(100)     ,
   Solde DECIMAL             
);

create table Artiste
(
   numArtiste int primary key,
   Nom varchar(200)          ,
   DateNaissance date        ,
   Nationalite enum('France','Belgique','USA','UK','Canada','Russie','Allemagne','Autriche','Suisse','Japon','Espagne')           
);

create table Distributeur
(
   numDistributeur int primary key,
   Nom varchar(50)                ,
   Adresse varchar(100)     
);

create table Categorie
(
  numCategorie varchar(50) primary key
);

create table Film
(
   numFilm int primary key,
   Titre varchar(200)     ,
   Pays enum('France','Belgique','USA','UK','Canada','Australie','Allemagne','Autriche','Suisse','Japon','Espagne'),
   Annee int              ,
   Note float             ,
   Duree float            ,
   Langue enum('Francais','Anglais','Japonais','Espagnol','Allemand'),
   numDistributeur int    , 
   foreign key (numDistributeur) references Distributeur(numDistributeur)
);

create table Stock
(
   numFilm  int                   ,  
   numMagasin int                 ,
   Copies int                     ,
   primary key(numFilm,numMagasin), 
   foreign key(numFilm) references Film(numFilm),
   foreign key(numMagasin) references Magasin(numMagasin)

);

create table Classification
(
  numCategorie varchar(50),
  numFilm      int        ,
  primary key(numCategorie,numFilm),
  foreign key (numFilm) references Film(numFilm) ,
  foreign key (numCategorie) references Categorie(numCategorie) 
);

create table Joue
(
   numFilm    int                 ,
   numArtiste int                 ,  
   primary key(numArtiste,numFilm),
   foreign key (numFilm) references Film(numFilm) ,
   foreign key (numArtiste) references Artiste(numArtiste) 

);

create table Realisation
(
   numFilm    int                 ,
   numArtiste int                 ,  
   primary key(numArtiste,numFilm),
   foreign key (numArtiste) references Artiste(numArtiste) 
);

create table Location
(
   numLocation int primary key auto_increment,
   numFilm  int                ,  
   numClient int               ,
   DateDe date                 ,
   DateA date                  ,
   numMagasin int              , 
   foreign key (numFilm) references Film(numFilm) ,     
   foreign key(numMagasin) references Magasin(numMagasin),
   foreign key(numClient) references Client(numClient)
      
);

insert into Distributeur values (1,'Constance Film',NULL);
insert into Distributeur values (2,'Classique Film',NULL);
insert into Distributeur values (3,'Best Film',NULL);

insert into Categorie values ('Comedie'),('Drame'),('Thriller'),('Horreur'),('Dessin anime'),('Policier'),('Science-fiction'),('Aventure');

insert into Film values(1,'Perfect World','USA',1993,7.0,138,'Anglais',1); 
insert into Film values(2,'The terminator','USA',1984,7.9,108,'Anglais',1);
insert into Film values(3,'Le père Noël est une ordure','France',1978,7.2,87,'Francais',2); 
insert into Film values(4,'Pulp Fiction','USA',1994,8.7,154,'Anglais',2); 
insert into Film values(5,'Good Bye, Lenin!','Allemagne',2003,7.9,121,'Allemand',2); 
insert into Film values(6,'Dirty Harry','USA',1971,7.8,103,'Anglais',1); 
insert into Film values(7,'Pour les tests','France',1971,NULL,NULL,'Français',2); 

insert into Classification values('Drame',1);
insert into Classification values('Aventure',2);
insert into Classification values('Comedie',3);
insert into Classification values('Drame',4);
insert into Classification values('Comedie',5);
insert into Classification values('Drame',5);
insert into Classification values('Policier',6);

insert into Artiste values (1,'Clint Eastwood','1930-05-31','USA');
insert into Artiste values (2,'Kevin Costner','1955-01-18','USA');
insert into Artiste values (3,'Laura Dern','1967-02-10','USA');
insert into Artiste values (4,'James Cameron','1954-08-16','Canada');
insert into Artiste values (5,'Arnold Schwarzenegger','1947-07-30','Autriche');
insert into Artiste values (6,'Michael Biehn','1956-07-31','USA');
insert into Artiste values (7,'Linda Hamilton','1956-09-26','USA');
insert into Artiste values (8,'Quentin Tarantino','1963-03-27','USA');
insert into Artiste values (9,'John Travolta','1954-02-18','USA');
insert into Artiste values (10,'Bruce Willis','1955-03-19','USA');
insert into Artiste values (11,'Uma Thurman','1970-04-29','USA');
insert into Artiste values (12,'Wolfgang Becker','1954-06-22','Allemagne');
insert into Artiste values (13,'Daniel Brühl','1978-06-16','Allemagne');
insert into Artiste values (14,'Katrin Sass','1956-10-23','Allemagne');
insert into Artiste values (15,'Chulpan Khamatova','1975-10-01','Russie');
insert into Artiste values (16,'Don Siegel','1912-10-26','USA');
insert into Artiste values (17,'Andrew Robinson','1942-02-14','USA');
insert into Artiste values (18,'Anémone','1950-08-09','France');
insert into Artiste values (19,'Thierry Lhermitte','1952-11-24','France');
insert into Artiste values (20,'Marie-Anne Chazel','1951-09-19','France');
insert into Artiste values (21,'Christian Clavier','1952-05-06','France');
insert into Artiste values (22,'Jean-Marie Poiré','1945-07-10','France');
insert into Artiste values (23,'Juste PourCorser',NULL,'France');

insert into Client values (1,'Vincent','chez Vincent',12.5 ), (2,'Denis','chez Denis',22.5 ),(3,'Marie','chez Marie',2.5),(4,'Françoise','chez Françoise',34.5);

insert into Magasin values (1,'magasin1'),(2,'magasin2');

insert into Joue values (1,1),(1,2),(1,3);
insert into Joue values (2,5),(2,6),(2,7),(2,23);
insert into Joue values (3,18),(3,19),(3,20),(3,21);
insert into Joue values (4,9),(4,10),(4,11);
insert into Joue values (5,13),(5,14),(5,15);
insert into Joue values (6,1),(6,17);

insert into Realisation values (1,1),(2,4),(3,22),(4,8),(5,12),(6,16),(7,23);

insert into Location (numFilm,numClient,DateDe,DateA,numMagasin) values (1,1,'2019-01-03','2019-01-13',1);
insert into Location (numFilm,numClient,DateDe,DateA,numMagasin)values (2,1,'2019-01-03','2019-01-13',1);
insert into Location (numFilm,numClient,DateDe,DateA,numMagasin)values (4,1,'2019-01-13','2019-01-23',1);
insert into Location (numFilm,numClient,DateDe,DateA,numMagasin)values (6,1,'2019-01-13',NULL,1);
insert into Location (numFilm,numClient,DateDe,DateA,numMagasin)values (5,1,'2019-01-26','2019-01-30',2);
insert into Location (numFilm,numClient,DateDe,DateA,numMagasin)values (6,1,'2019-02-03','2019-03-12',2);
insert into Location (numFilm,numClient,DateDe,DateA,numMagasin)values (4,2,'2019-01-12','2019-01-18',1);
insert into Location (numFilm,numClient,DateDe,DateA,numMagasin)values (6,2,'2019-01-12','2019-01-18',1);
insert into Location (numFilm,numClient,DateDe,DateA,numMagasin)values (3,2,'2019-01-12',NULL,1);
insert into Location (numFilm,numClient,DateDe,DateA,numMagasin)values (1,3,'2019-01-26','2019-02-05',2);
insert into Location (numFilm,numClient,DateDe,DateA,numMagasin)values (2,3,'2019-02-03','2019-02-05',2);
insert into Location (numFilm,numClient,DateDe,DateA,numMagasin)values (4,3,'2019-01-12','2019-02-05',1);

insert into Stock values (1,1,4),(1,2,10);
insert into Stock values (2,1,3),(2,2,5);
insert into Stock values (3,1,10),(3,2,5);
insert into Stock values (4,1,5);
insert into Stock values (5,2,10);
insert into Stock values (6,1,4),(6,2,10);



