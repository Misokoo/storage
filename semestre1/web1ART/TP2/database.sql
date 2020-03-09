drop table if exists Client;

create table Client
(
   numClient int primary key AUTO_INCREMENT NOT NULL,
   Nom varchar(50)
);
insert into Client values (1,'John Doe'), (2,'Jane Doe'),(3,'Jaina Solo'),(4,'Kyle Katarn'), (5,'Satele Shan');
