create table xRawMaterial
(MaterialID char(3), 
Description varchar(50), 
UnitOfMeasure char(8), 
StandardPrice money Check(standardprice >0), 
constraint pkRawMaterial primary key (MaterialID));

create table xVendorMaterial
(VendorID char(4), 
 MaterialID char(3), 
 CurrentPrice money Not null, 
 constraint pkVendorMaterial
 primary key (VendorID, MaterialID),
 constraint fkVendor
 Foreign key (VendorID) References xVendor (vendorID), 
 constraint fkRM
 foreign key (MaterialID) references xRawMaterial (MaterialID));

 create table xMaterialLocation
 (VendorID char(4),
 MaterialID char(3), 
 LocationID char(3), 
 QuantityOnHand decimal(8,3),
 constraint pkMaterialLocation
 primary key (VendorID, MaterialID, LocationID),
 constraint fkVendorMaterial
 foreign key (VendorID, MaterialID)
 references xVendorMaterial (VendorID, MaterialID));



Insert into xRawMaterial values(
'255', 'Concrete Overlay Polymer', 'pound', 13.75),
('240', 'Mortar Mix', null ,.23),
('271', 'Graphite Isomolded Sheet', 'each',46.70);
 
Insert into xVendorMaterial values(
'7819', '255', 14.25),
('62', '255', 13.95),
('0062', '271', 46.70),
('7819', '240', .26);


Insert into xMaterialLocation values(
'7819', '255', 12, 700.25),
('7819', '255', 15 , 600.88),
('7819', '240', 12, 124),
('0062', '271', 81 , 5505),
('7819', '255', 81 , 6);

select *
from xVendorMaterial;

select *
from xMaterialLocation;


