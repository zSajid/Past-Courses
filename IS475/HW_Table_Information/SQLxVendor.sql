Create table xVendor(
VendorID char(4),
VendorName varchar(30),
FirstBuyDate datetime
Constraint pkVendor Primary Key(vendorID));

Insert into xVendor values(
'7819', 'Martinson Concrete and Supply', '04/15/2015'),
('2745', 'Johnson Plating', '14-oct-2014'),
('0062', 'Evergreen Surface Products', '01-12-2016');

Select * 
from xVendor;

insert into xVendor values
(0062, 'Touchstone Materials', '05-16-15');

select *
from xVendor;

select VendorID, 
	VendorName
From xVendor
where VendorID = '0062';