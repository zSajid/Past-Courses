create table xtblEmployee(
employeeID int primary key, 
LastName varchar(50) not null, 
FirstName varchar(50) not null, 
Birthdate date, 
hiredate datetime Not Null, 
EmpMgrID int,
constraint empmgrfk foreign key (empmgrid) references xtblemployee(employeeID)
);

select *
from xtblEmployee;
