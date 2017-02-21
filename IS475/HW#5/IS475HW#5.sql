create table tblVendor(
VendorID char(5) primary key not null,
Name varchar(30) not null, 
Address1 varchar(30) not null,
Address2 varchar(30), 
City varchar(20) not null, 
State char(2) not null, 
Zip varchar(12) not null,
Email varchar(30), 
Contact varchar(30), 
Phone char(15) not null, 
FirstBuyDate Datetime not null
);

create table tblEmployee(
EmpID char(6) primary key not null, 
EmpLastName varchar(30) not null, 
EmpFirstName varchar(30) not null, 
EmpEmail varchar(30), 
EmpPhone char(15) not null, 
EmpMgrID char(6),
constraint tblEmpmgrfk foreign key (empmgrid) references tblemployee(EmpID)
);

create table tblCondition(
ConditionID char(2) primary key not null, 
Description varchar(30) not null
);

create table tblPurchaseOrder(
PoNumber char(6) primary key not null,  
PODatePlaced datetime not null, 
PODateNeeded datetime, 
Terms varchar(15), 
Conditions varchar(15), 
BuyerEmpID char(6), 
constraint tblPurchaseOrderEmpIDfk foreign key(BuyerEmpID) references tblEmployee(EmpID),
VendorID char(5) not null,
constraint tblPurchaseOrderVendorIDfk foreign key(VendorID) references tblVendor(VendorID)
);

create table tblProductType(
ProducttypeID char(2) primary key not null, 
Description varchar(30) not null
);

create table tblProduct(
ProductID char(5) primary key not null, 
Description varchar(30) not null, 
UOM char(10) check (UOM = 'each' or UOM = 'feet' or UOM = 'inches' or UOM = 'meters' 
or UOM = 'cm' or UOM = 'sheet' or UOM = 'case'),
EOQ decimal(6,2),
QOH decimal(8,2) not null, 
ProductTypeID char(2) not null, 
constraint tblProductProductTypeIDfk foreign key(ProductTypeID) references tblProductType( ProducttypeID)
);


create table tblPurchaseOrderLine(
PONumber char(6)  not null,
ProductID char(5)  not null, 
QtyOrderered decimal(6,2)  Check(QtyOrderered >0), 
Price money not null, 
DateNeeded datetime  not null,
CONSTRAINT tblPurchaseOrderLineTripleStackPK

PRIMARY KEY (PONumber, DateNeeded, ProductID),
/*  constraint uk_ab Unique (PONumber,DateNeeded, ProductID)*/

);

/* Finish this up*/
CREATE TABLE		tblreceiver
(receiverID     		Int 	identity (1,1),
datereceived		DATETIME not null,
 ponumber		CHAR(6),
 productID		CHAR(5),
 dateneeded		DATETIME,
 qtyreceived		DECIMAL(6,2) check(qtyreceived > 0),
 conditionID		CHAR(2)	REFERENCES tblcondition(conditionID),
 receiveempid		CHAR(6)	REFERENCES tblemployee(empid),
);





create table tblPurchaseHistory(
HistoryID int  identity(1,1) primary key,
ProductID char(5) not null, 
DatePurchased datetime not null,
Qty decimal(8,2) not null, 
Price money not null, 
VendorID  char(5), 
constraint tblPurchaseHistoryVendorIDfk foreign key(VendorID) references tblVendor(VendorID)
);


drop table tblReceiver;
drop table tblPurchaseOrderLine;
drop table tblVendor;
drop table tblProductType;
drop table tblCondition;
drop table tblPurchaseHistory;
drop table tblProduct;
drop table tblPurchaseOrder;
drop table tblEmployee;

