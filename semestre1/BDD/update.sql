drop table if exists V;
drop table if exists U;

create table U(i int primary key , j int)engine = innodb;
create table V(k int primary key , i int, foreign key (i) references U(i)) engine = innodb;

insert into U values (1,10),(2,20),(3,30);
insert into V values (1,1),(2,1),(3,2);

select U.i as Ui, U.j as Uj, V.k as Vk, V.i as Vi  
from U left join V on U.i=V.i;


