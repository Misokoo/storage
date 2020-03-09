drop table if exists Contrat;
drop table if exists Client;


create table Client
(
   numClient int primary key,
   nom varchar(50)
)engine = innodb;

create table Contrat
(
   numContrat int primary key,
   numClient int foreign key references Client(numClient),
   adresse varchar(50)
)engine = innodb;


insert into Client values(1,'Jacques'),(2,'François'),(3,'Caroline');
insert into Contrat values (1,1,'Paris'),(2,1,'Strasbourg'),(3,3,'Nice');
insert into Contrat values (4,10,'Lyon');


// Exercice 2 Correction //

select F.Titre
from Film F inner join Distributeur D on F.numDistributeur = D.numDistributeur
where D.Nom = 'Constance Film';

select C.Nom
from Client C inner join Location L on C.numClient = L.numClient
              inner join Joue J on J.numFilm = L.numFilm
              inner join Artiste A on A.numArtiste = J.numArtiste
where A.Nom = 'Michael Biehn';

select M.adresse, F.Titre
from Magasin M inner join Stock S on S.numMagasin = M.numMagasin
               inner join Film F on F.numFilm = S.numFilm
	       inner join Classification C on C.numFilm = F.numFilm
where C.numCategorie = 'Drame';

select distinct F.Titre
from Joue J inner join Realisation R on R.numArtiste = J.numArtiste
            inner join Film F on F.numFilm = R.numFilm;

select distinct F.Titre
from Joue J inner join Realisation R on R.numArtiste = J.numArtiste
            inner join Film F on F.numFilm = J.numFilm;

select F.Titre
from Joue J inner join Realisation R on R.numArtiste = J.numArtiste and R.numFilm = J.numFilm
            inner join Film F on F.numFilm = R.numFilm;


update Client C natural join Location L
set C.Solde = C.Solde - 5
where L.numLocation=3;

// Exercice 3 Correction //


select count(distinct F.numFilm)
from Film F inner join Distributeur D on F.numDistributeur = D.numDistributeur
where D.Nom = 'Constance Film';

select D.Nom,count(distinct F.numFilm)
from Film F right join Distributeur D on F.numDistributeur = D.numDistributeur
group by D.numDistributeur,D.Nom;

select D.Nom,count(distinct F.numFilm) as Nbre
from Film F right join Distributeur D on F.numDistributeur = D.numDistributeur
group by D.numDistributeur,D.Nom
having count(distinct F.numFilm)>=4;
/*On peut aussi ecrire having Nbre >4*/

select count(distinct numClient)
from Client;

select C.Nom, M.Adresse, count(distinct L.numLocation)
from Client C CROSS JOIN Magasin M
     left join Location L on L.numMagasin = M.numMagasin and L.numClient=C.numClient
group by C.numClient,M.numMagasin,C.Nom,M.adresse;


select  C.Nom, M.Adresse, count(distinct L.numLocation) as nbTotal
from Client C CROSS JOIN Magasin M
     inner join Location L on L.numMagasin = M.numMagasin and L.numClient=C.numClient
     inner join Film F on L.numFilm = F.numFilm
     inner join Joue J on J.numFilm = L.numFilm
     inner join Artiste A on J.numArtiste = A.numArtiste
where A.Nom= 'Clint Eastwood'
group by C.numClient,M.numMagasin,C.Nom,M.adresse
having nbTotal>1;

// Exercice 5 Correction //
1)
select count(distinct L.numLocation)
from Location L
where L.dateA is null;

2)
select L.numLocation, Adddate(L.DateDe,interval 14 day)as Arendre
from Location L
where L.dateA is null;

3)
select L.numLocation, DATEDIFF(Adddate(L.DateDe,interval 14 day), CURDATE())
from Location L
where L.dateA is null ;

4)
select L.numLocation
from Location L
where L.dateA is null and DATEDIFF(Adddate(L.DateDe,interval 14 day), CURDATE()) < 0 ;

5)
select L.numLocation
from Location L
where L.dateA is not null and DATEDIFF(Adddate(L.DateDe,interval 14 day), L.dateA)<0;

6)
select L.numLocation
from Location L
where L.dateA is null and DATEDIFF(Adddate(L.DateDe,interval 14 day), CURDATE()) <0
union
select L.numLocation
from Location L
where L.dateA is not null and DATEDIFF(Adddate(L.DateDe,interval 14 day), L.dateA)<0;


7)
select C.Nom,count(distinct P.numLocationPb) from
Client C left join
  (select L.numLocation as numLocationPb, L.numClient as numClient
   from Location L
   where L.dateA is null and DATEDIFF(Adddate(L.DateDe,interval 14 day), CURDATE()) <0
   union
   select L.numLocation as numLocationPb, L.numClient as numClient
   from Location L
   where L.dateA is not null and DATEDIFF(Adddate(L.DateDe,interval 14 day), L.dateA) <0)P
  on P.numClient = C.numClient
group by C.numClient, C.Nom;
