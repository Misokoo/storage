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
   numClient int            ,   
   adresse varchar(50),
   CONSTRAINT C1
   FOREIGN KEY (numClient) 
   REFERENCES Client (numClient)
   ON DELETE { DELETE FROM Contrat WHERE numClient=numClient |SET NULL}      
)engine = innodb; 

insert into Client values(1,'Jacques'),(2,'François'),(3,'Caroline');
insert into Contrat values (1,1,'Paris'),(2,1,'Strasbourg'),(3,3,'Nice');
insert into Contrat values (4,10,'Lyon');

