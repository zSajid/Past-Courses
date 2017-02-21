create table tblReceiver(
ReceiverID int  identity(1,1) primary key,
DateReceieved datetime not null, 
PONumber char(6), 
ProductID char(5), 
DateNeeded datetime,
QtyReceieved decimal(6,2),
ConditionID char(2),
constraint tblReceiverConditionfk foreign key (ConditionID) references tblCondition( ConditionID),
ReceieveEmpId char(6),
constraint tblReceiverEmployeefk foreign key (ReceieveEmpId) references tblEmployee( EmpID),
constraint tblReceieverfk foreign key(PONumber, ProductID, DateNeeded) references tblPurchaseOrderLine(ponumber, ProductID, DateNeeded),
);
