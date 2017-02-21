/*Table Condition Input data starts here*/
insert into tblCondition values
('FD', 'Freight damage');

insert into tblCondition values
('IP', 'Improper packaging');

insert into tblCondition values
('OK', 'Acceptable');

insert into tblCondition values
('OT', 'Other');

insert into tblCondition values
('UK', 'Unknown');

insert into tblCondition values
('WD', 'Water Damage');

/* Product Type starts here*/
insert into tblProductType values
('CC', 'Camping and Cooking');


insert into tblProductType values
('CS', 'Camping and Resting');

insert into tblProductType values
('HT', 'Hiking and Trails');

insert into tblProductType values
('LA', 'Comfort Essentials');

insert into tblProductType values
( 'MS',	'Miscellaneous'	);


insert into tblProductType values
('PG', 'Travel Bags');

insert into tblProductType values
('UT', 'Utility Materials');

/*employee data input starts here*/
insert into tblEmployee values
('E10003',	'Armstrong',	'Evelyn',	'EARMSTRONG@yahoo.com',	'7755423212',null); 	
	   
insert into tblEmployee values
('E10009', 'Hernandez',	'Nathan', null, 	'7755313562','E10003');
	   
insert into tblEmployee values
('E10015',	'Fetters',	'Sam',	'SFETTERS@yahoo.com',	'7753453821', 	'E10003');
	   
insert into tblEmployee values
('E10018',	'Schnitkowski',	'Michael',	'MSCHNIT@yahoo.com', '7776553582', 	'E10003');
	   
insert into tblEmployee values
('E10026', 'Williams',	'Barbara Ray',	'BWILLIAMS@yahoo.com',	'7755313834', 	'E10015');

	   
insert into tblEmployee values
('E10042', 'Van Meter', 'Juliette',	'JVANMETER@yahoo.com',	'7758453551' ,	'E10026');	   

insert into tblEmployee values
('E10055',	'Smith',	'Jeannie Anne',	'JSMITH2@yahoo.com',	'7759153891',null);
 		   
insert into tblEmployee values
('E10056',	'Chen',		'John',			null	,	'7759053821',	'E10015');
	   
insert into tblEmployee values
('E10057', 	'Pinot',	'Jean Claude',	'JPINOT@yahoo.com',	'7756749002', null); 		   

insert into tblEmployee values
('E10077',	'MacAndrews-Abernethy'	,'Elizabeth Victoria'	,'EMACANDREWSABERNET@yahoo.com',	'7755553894', 	'E10026');	   

insert into tblEmployee values
('E10085',	'Wong'	,'Thomas',	'TNG@yahoo.com'	,'7757783511', 	'E10026');	   

insert into tblEmployee values
('E10087',	'Ursenbach',	'Wolter',	'WURSENBACH@yahoo.com',	'7757821341', 	'E10026');

	   
insert into tblEmployee values
('E10088',	'O''Toole',	'Timothy',		'TOTOOL@yahoo.com',	'7758423529', 	'E10026');
	   
insert into tblEmployee values
('E10101',	'Kelly',	'Kendall',	'KKELLY@yahoo.com'	,'7758413838' ,	'E10026');	
   
insert into tblEmployee values
('E10192',	'Alberghetti',	'Antonio',	null		, '7756219005', null); 		 


/*Vendor input data starts here*/
 
insert into tblVendor values('00216', 'PolySort Manufacturing', 	'2550 23rd Avenue', null, 		'Denver',	'CO',	'80568',	'fxd@polysort.com',	'Francisco Delgado',	'3035558123', 	'7/28/2015');	   

insert into tblVendor values('09567',	'Apex Mills',	'3500 Industrial Parkway',	'Unit 7',	'SPARKS',	'Nv',	'89431',	'tcc@yahoo.com', null, 		'7755552894', 	'3/13/2012');

	   
insert into tblVendor values('13135',	'Adventure Materials',	'P.O. Box 2700', null, 	'SALT LAKE CITY',	'UT',	'84560-2700',	'info@advmat.com', null, 		'8015554500', '8/4/2015');
	   
insert into tblVendor values('17453',	'Albemarle Corporation',	'2355-B Vista Drive',	'Suite 765-B',	'Sparks',	'NV',	'89431', 'sandp@msn.com',	'maryanne Jones',	'7755553451', 	'6/14/1998');	   
insert into tblVendor values('18567',	'Alcan Plastic, Inc.',	'P.O. Box 4456',			null,		'Eagle Falls',	'AK',	'99565', 'alcanp@plastic.com', null, 		'9075555268',	'5/15/2015');	   

insert into tblVendor values('20566',	'BestCo Food Equipment',	'1515 Kendall Mill Road', null, 	'Allentown',	'PA',	'15003',	'buyer@best.com',	null,	'4845556789', 	'9/14/2016');	   

insert into tblVendor values('22890',	'Kitchen Chemicals Corp.',	'7750 Rock Blvd.',		null, 'sparks', 'nv', '89431-5602', 'info@kchem.corp', 'melinda', '7755552566', 	'7/23/2012');	   
insert into tblVendor values('36257',	'Injectomatic Mold Corp.',	'14557 Hawthorne Blvd.',	'Unit 14',	'los angeles',	'CA',	'90036-9960',	'hayman@inject.com',	'Sam hayes',	'2135554963' ,	'6/15/2016');	   

insert into tblVendor values('45899',	'Celanette Design, LLC', '9865 Sepulveda Blvd.', 'Suite B', 'Los Angeles',	'ca',	'90045-3660', 	'buyer@celanette.com',	'Linda Burch',	'3105555545', 	'9/23/2016');	   
insert into tblVendor values('87654',	'Recycle Plastics Company',	'10 Riverview Highway', null,	'detroit',		'mi',	'48050',	'vendor@rpc.com',	null,	'3135554266', 	'8/16/2013');	 


/*PurchaseOrder starts here*/
insert into tblPurchaseOrder values
('025974',	'8/15/2016',	 '8/18/2016',	'Net 15',	'FOB-AIR',	'E10015',	'18567');

insert into tblPurchaseOrder values
('045687',	'8/21/2016',	 '9/12/2016',	'COD'	,	null	,	'E10055'	,'00216');
	   
insert into tblPurchaseOrder values
('056489',	'8/4/2016',	 '8/15/2016',	 null,		'FOB',		'E10055',	'36257');

insert into tblPurchaseOrder values
('112233',	'9/21/2016',	 '10/25/2016',	'Net10',		null	,    'E10026'	,'17453');

insert into tblPurchaseOrder values
('234607',	'9/4/2016',	 '9/28/2016',	'Net 30',	'FOB',		'E10055',	'17453');
	   
insert into tblPurchaseOrder values
('256887',	'9/19/2016',	 '10/15/2016',	'Net 30',	'FOB',		null	,	'87654');
	   
insert into tblPurchaseOrder values
('329987',	'10/10/2016', '1/12/2017',	'Net 30',	'FOB',		'E10101',	'18567'	);
   
insert into tblPurchaseOrder values
('365870',	'9/14/2016',	 '3/14/2017',	'Net 30',	null,		'E10101',	'17453');
	   
insert into tblPurchaseOrder values
('543791',	'9/15/2016',	 '1/15/2017',	'Net 30',	null,		'E10055',	'45899');	   


insert into tblPurchaseOrder values
('600124',	'10/1/2016',	 '12/20/2016',	'COD'	,	null	,	'E10055'	,'00216');

	   
insert into tblPurchaseOrder values
('661677',	'9/30/2016',	 '11/15/2016',	'Net 15',	'FOB'	,	'E10101'	,'00216');	
   

insert into tblPurchaseOrder values
('781900'	,'10/3/2016',	 '11/12/2016',	 null	,	'FOB'	,	'E10055'	,'09567');
	   
insert into tblPurchaseOrder values
('902347',	'9/16/2016'	, '10/18/2016',	 null	,	'Pickup',	'E10087',	'09567');	 

/* tblProduct data entry*/
insert into tblProduct values('A7879',	'Canvas, Non-Woven',	'feet', 	2000,1200,	'CS');	   
insert into tblProduct values('C2399',	'Thermoplastic',	'sheet' 	,10,	5,	'CS');	   
insert into tblProduct values('C9100',	'Unbleached Muslin',	'meters' ,	8000,	5500,	'CS');	   
insert into tblProduct values('G0983',	'Alpine Small Pot',	'each', 	100,	65,	'HT');	   
insert into tblProduct values('G1258',	'Alpine Pot/Kettle Handle',	'each', 	50,	96,	'UT');	   
insert into tblProduct values('G1366',	'Alpine Pot/Kettle Insert',	'each', 	48	,55,	'UT');   
insert into tblProduct values('G5698',	'Alpine Skillet Handle Set',	'each', 	48,	50,	'UT');	   
insert into tblProduct values('J8006',	'Microfilter tubing',	'feet',450	,550,	'MS');	   
insert into tblProduct values('L8500',	'Hiking Lounge Seating - Blue',	'each', 	15,	1	,'LA');	   
insert into tblProduct values('L8501',	'Hiking Lounge Seating - Gray',	'each', 	10,	0	,'LA');   
insert into tblProduct values('M2356',	'Cot Mesh - Ultralite',	'meters' , 1000,	1200,	'MS');	   
insert into tblProduct values('M3577',	'Cot Mesh - Sturdy',	'feet',	300,	650,	'MS');	   
insert into tblProduct values('O1957',	'Poly pro tubing, 1/2"',	'feet',	300,	95,	'MS');	   
insert into tblProduct values('P5678',	'Stuff Sacks - Pillow Size',	'case', 	48	,40,	'PG');	   
insert into tblProduct values('P7844',	'Down Baffle Liner'	,'meters', 	50,	45,	'MS');	   
insert into tblProduct values('R5660',	'Water Filtration Pump',	'each', 	30,	25,	'CC');	   
insert into tblProduct values('T0460',	'Alpine Water Bottle'	,'each', 	100,	15,	'CC');	 

/*tbl Purchase History */


insert into tblPurchaseHistory values('A7879',	'7/21/2013',10000,	$0.07,	'09567'	);   
insert into tblPurchaseHistory values('A7879',	'3/15/2014',10000,	$0.08,	'09567'	);   
insert into tblPurchaseHistory values('A7879',	'10/16/2015',	8000,	$0.10,	'17453'	);   
insert into tblPurchaseHistory values('A7879',	'3/15/2016',7500,	$0.12,	'17453'	);   
insert into tblPurchaseHistory values('C2399',	'4/14/2013',3000,	$1.45,	'87654'	);   
insert into tblPurchaseHistory values('C2399',	'1/25/2015',150,	$1.75,	'36257'	  ); 
insert into tblPurchaseHistory values('C2399',	'3/22/2015',100,	$1.95,	'87654'	  ); 
insert into tblPurchaseHistory values('C2399',	'8/15/2015',150,	$1.75,	'36257'	  ); 
insert into tblPurchaseHistory values('C2399',	'2/12/2016',100,	$1.99,	'87654'	  ); 
insert into tblPurchaseHistory values('C2399',	'5/16/2016',350,	$1.94,	'18567'	  ); 
insert into tblPurchaseHistory values('C2399',	'6/4/2016',200,	$1.55,  	'87654'	   );
insert into tblPurchaseHistory values('C2399',	'8/12/2016',350,	$1.89,	'18567'	  ); 
insert into tblPurchaseHistory values('G0983',	'2/10/2014',90,	$2.15,	  '20566'	  ); 
insert into tblPurchaseHistory values('G0983',	'5/10/2014',250,	$2.11,	'18567'	  ); 
insert into tblPurchaseHistory values('G0983',	'7/20/2014',300,	$2.10,	'18567'	  ); 
insert into tblPurchaseHistory values('G0983',	'9/22/2015',200,	$2.38,	'17453'	  ); 
insert into tblPurchaseHistory values('G0983',	'1/18/2016',250,	$1.99,	'00216'	  ); 
insert into tblPurchaseHistory values('G0983',	'3/12/2016',75,	$2.15,	  '17453'	  ); 
insert into tblPurchaseHistory values('G1258',	'6/20/2016',25,	$4.29,	  '20566'	  ); 
insert into tblPurchaseHistory values('G1258',	'7/21/2016',25,	$4.29,	  '20566'	  ); 
insert into tblPurchaseHistory values('G1366',	'6/20/2016',25,	$4.81,	  null	   );
insert into tblPurchaseHistory values('G5698',	'6/15/2015',200,	$2.16,	null	   );
insert into tblPurchaseHistory values('G5698',	'6/20/2016',25,	$2.21,	  null	   );
insert into tblPurchaseHistory values('L8500',	'4/21/2014',2,	$29.45,	  '13135'	  ); 
insert into tblPurchaseHistory values('L8500',	'2/2/2015',5,	$38.40,     	'13135'	   );
insert into tblPurchaseHistory values('L8500',	'12/12/2015',	10,	$26.22,  	'13135'	);   
insert into tblPurchaseHistory values('L8501',	'12/12/2015',	15,	$29.94,	  '13135'	);   
insert into tblPurchaseHistory values('M3577',	'5/12/2013',3200,	$4.85,	'18567'	);   
insert into tblPurchaseHistory values('M3577',	'12/2/2013',1200,	$5.62,	'18567'	);   
insert into tblPurchaseHistory values('M3577',	'2/10/2014',1200,	$5.62,	'18567'	);   
insert into tblPurchaseHistory values('M3577',	'3/10/2014',1509,	$5.59,	'18567'	);   
insert into tblPurchaseHistory values('M3577',	'8/15/2014',200,	$5.95,	'87654'	  ); 
insert into tblPurchaseHistory values('M3577',	'11/6/2015',300,	$6.25,	'87654'	  ); 
insert into tblPurchaseHistory values('M3577',	'1/10/2016',100,	$5.91,	'87654'	  ); 
insert into tblPurchaseHistory values('M3577',	'7/12/2016',150,	$6.35,	'18567'	  ); 
insert into tblPurchaseHistory values('O1957',	'11/2/2014',2500,	$0.42,	'18567'	);   
insert into tblPurchaseHistory values('O1957',	'7/19/2015',450,	$0.41,	'00216'	  ); 
insert into tblPurchaseHistory values('O1957',	'9/18/2015',2500,	$0.42,	'20566'	);   
insert into tblPurchaseHistory values('O1957',	'10/3/2015',100,	$0.65,	'18567'	  ); 
insert into tblPurchaseHistory values('O1957',	'1/12/2016',1400,	$0.53,	'00216'	);   
insert into tblPurchaseHistory values('O1957',	'5/7/2016',450,	$0.44,	  '00216'	   );
insert into tblPurchaseHistory values('O1957',	'7/23/2016',200,	$0.43,	'20566'	  ); 
insert into tblPurchaseHistory values('P5678',	'6/12/2016',250,	$23.51, null		   );
insert into tblPurchaseHistory values('P7844',	'7/12/2016',2570,	$0.67,  null	   );
insert into tblPurchaseHistory values('R5660',	'2/27/2015',80,	$2.15,	  '17453'	  ); 
insert into tblPurchaseHistory values('R5660',	'5/23/2016',80,	$2.12,	  '17453'	  ); 
insert into tblPurchaseHistory values('R5660',	'6/18/2016',4500,	$2.10, 	null	   );
insert into tblPurchaseHistory values('T0460',	'3/29/2014',1200,	$1.12,	'45899'	);   
insert into tblPurchaseHistory values('T0460',	'3/12/2015',1200,	$1.76,	'45899'	);   
insert into tblPurchaseHistory values('T0460',	'2/19/2016',1500,	$1.98,	'45899'	); 


/*tblePurchaseOrderline*/
insert into tblPurchaseOrderLine values('025974',	'M3577', 600	 , $4.63	, '8/18/2016');  
insert into tblPurchaseOrderLine values('025974',	'O1957', 300	 , $0.46	, '8/18/2016');  
insert into tblPurchaseOrderLine values('045687',	'C2399', 40	   , $2.99	, '9/5/2016'); 
insert into tblPurchaseOrderLine values('045687',	'L8500', 15	   , $29.64, '9/10/2016');   
insert into tblPurchaseOrderLine values('045687',	'O1957', 450	 , $0.29	, '9/12/2016');  
insert into tblPurchaseOrderLine values('056489',	'M3577', 600	 , $5.29	, '8/15/2016');  
insert into tblPurchaseOrderLine values('112233',	'M3577', 600.6,	$5.89	, '10/7/2016');  
insert into tblPurchaseOrderLine values('112233',	'P7844', 500.25,	$1.50	, '9/24/2016');  
insert into tblPurchaseOrderLine values('234607',	'C2399', 75	   , $1.75	, '9/6/2016'); 
insert into tblPurchaseOrderLine values('234607',	'G0983', 200	 , $1.50	, '9/8/2016'); 
insert into tblPurchaseOrderLine values('234607',	'G1366', 182	 , $4.89	, '9/10/2016');  
insert into tblPurchaseOrderLine values('234607',	'G5698', 182   ,	$1.22	, '9/19/2016');  
insert into tblPurchaseOrderLine values('234607',	'R5660', 100 	 , $1.99	, '9/26/2016');  
insert into tblPurchaseOrderLine values('234607',	'T0460', 200	 , $2.75	, '9/26/2016');  
insert into tblPurchaseOrderLine values('256887',	'C2399', 20	   , $2.50	, '10/15/2016');   
insert into tblPurchaseOrderLine values('256887',	'P5678', 48	   , $22.50, '10/15/2016');	   
insert into tblPurchaseOrderLine values('329987',	'O1957', 300	 , $0.41	, '11/15/2016');   
insert into tblPurchaseOrderLine values('329987',	'T0460', 50	   , $3.10	, '1/12/2017');  
insert into tblPurchaseOrderLine values('365870',	'G0983', 120	 , $1.85	, '12/14/2016');   
insert into tblPurchaseOrderLine values('365870',	'R5660', 75	   , $1.59	, '11/10/2016');   
insert into tblPurchaseOrderLine values('365870',	'T0460', 120	 , $2.39	, '3/14/2017');  
insert into tblPurchaseOrderLine values('543791',	'G0983', 100	 , $1.89	, '9/17/2016');  
insert into tblPurchaseOrderLine values('543791',	'G0983', 20	   , $2.19	, '9/28/2016');  
insert into tblPurchaseOrderLine values('543791',	'G0983', 20	   , $2.25	, '10/2/2016');  
insert into tblPurchaseOrderLine values('543791',	'G0983', 25	   , $2.25	, '10/12/2016');   
insert into tblPurchaseOrderLine values('543791',	'G0983', 45	   , $2.15	, '11/15/2016');   
insert into tblPurchaseOrderLine values('543791',	'G0983', 25	   , $2.15	, '12/10/2016');   
insert into tblPurchaseOrderLine values('543791',	'G1366', 48	   , $1.89	, '1/10/2017');  
insert into tblPurchaseOrderLine values('543791',	'G5698', 12	   , $1.95	, '10/15/2016');   
insert into tblPurchaseOrderLine values('543791',	'G5698', 48	   , $2.38	, '1/10/2017');  
insert into tblPurchaseOrderLine values('543791',	'T0460', 120  ,	$1.89	, '10/12/2016');   
insert into tblPurchaseOrderLine values('543791',	'T0460', 50	   , $2.49	, '12/15/2016');   
insert into tblPurchaseOrderLine values('600124',	'G0983', 100  ,	$1.96	, '10/18/2016');   
insert into tblPurchaseOrderLine values('600124',	'G1366', 150	 , $4.85	, '10/18/2016');   
insert into tblPurchaseOrderLine values('600124',	'G5698', 100   ,	$1.87	, '10/18/2016');   
insert into tblPurchaseOrderLine values('661677',	'L8500', 8	   , $26.45, '	11/15/2016');	   
insert into tblPurchaseOrderLine values('781900',	'C9100', 800	 , $3.45	, '10/15/2016');   
insert into tblPurchaseOrderLine values('781900',	'M3577', 750  ,	$5.55	, '11/10/2016');   
insert into tblPurchaseOrderLine values('902347',	'G0983', 100	 , $2.25	, '10/15/2016');   
insert into tblPurchaseOrderLine values('902347',	'T0460', 100	 , $2.25	, '9/22/2016');  
insert into tblPurchaseOrderLine values('902347',	'T0460', 450  ,	$1.39	, '12/5/2016');
insert into tblPurchaseOrderLine values('661677', 'L8500', 8, $26.45, '11/15/2016');

insert into tblReceiver values('8/16/2016','025974',	'M3577',	 '8/18/2016',  100	  ,  'OK'	 ,       null);
insert into tblReceiver values('8/15/2016','025974',	'M3577',	 '8/18/2016',  400	  ,  'OK'	 ,       null);
insert into tblReceiver values('8/17/2016','025974',	'M3577',	 '8/18/2016',  100	  ,  'WD'	 ,       null);
insert into tblReceiver values('8/15/2016','025974',	'O1957',	 '8/18/2016',  100	  ,  'OK'	 ,   'E10018');
insert into tblReceiver values('8/17/2016','025974',	'O1957',	 '8/18/2016',  210	  ,  'OK'	 ,   'E10018');
insert into tblReceiver values('9/5/2016' ,'045687',	'C2399',	 '9/5/2016', 40	    ,  'OK'	 ,   'E10042');
insert into tblReceiver values('9/14/2016','045687',	'C2399',	 '9/5/2016',11	     , 'FD'	 ,   'E10042');
insert into tblReceiver values('9/5/2016' ,'045687',	'O1957',	 '9/12/2016', 400	   ,   'OK'	 ,   'E10042');
insert into tblReceiver values('9/15/2016','045687',	'O1957',	 '9/12/2016',  40	   ,   'OK'	 ,   'E10042');
insert into tblReceiver values('9/7/2016' ,'234607',	'C2399',	 '9/6/2016', 13	    ,  'FD'	 ,   'E10018');
insert into tblReceiver values('9/8/2016' ,'234607',	'C2399',	 '9/6/2016', 22	    ,  'IP'	 ,   'E10018');
insert into tblReceiver values('9/12/2016','234607',	'C2399',	 '9/6/2016',40	     , 'WD'	 ,   'E10018');
insert into tblReceiver values('9/7/2016','234607',	'G0983',		 '9/8/2016',200	    ,  'WD'	 ,   'E10042');
insert into tblReceiver values('9/7/2016' ,'234607',	'G1366',	 '9/10/2016', 150	   ,   'OK'	 ,   'E10087');
insert into tblReceiver values('9/10/2016','234607',	'G1366',	 '9/10/2016',  25	   ,   'OK'	 ,   'E10087');
insert into tblReceiver values('9/14/2016','234607',	'G1366',	 '9/10/2016',  7	    ,  'OK'	 ,   'E10087');
insert into tblReceiver values('9/22/2016','234607',	'G5698',	 '9/19/2016',  182	  ,  'OK'	 ,       null);
insert into tblReceiver values('9/22/2016','234607',	'R5660',	 '9/26/2016',  50	   ,   'OK'	 ,       null);
insert into tblReceiver values('9/26/2016','234607',	'R5660',	 '9/26/2016',  50	   ,   'OK'	 ,       null);
insert into tblReceiver values('9/22/2016','234607',	'T0460',	 '9/26/2016',  200	  ,  'OK'	 ,   'E10087');
insert into tblReceiver values('9/23/2016','256887',	'P5678',	 '10/15/2016',	40	    ,  'OK'	 ,       null);
insert into tblReceiver values('9/25/2016','256887',	'P5678',	 '10/15/2016',	9	     ,   'OK'	 ,       null);
insert into tblReceiver values('9/26/2016','256887',	'C2399',	 '10/15/2016',	20	    ,  'OK'	 ,   'E10042');
insert into tblReceiver values('9/25/2016','543791',	'G0983',	 '9/17/2016',  50	   ,   'FD'	 ,   'E10042');
insert into tblReceiver values('9/24/2016','543791',	'G0983',	 '9/17/2016',  50	   ,   'OK'	 ,   'E10042');
insert into tblReceiver values('9/29/2016','543791',	'G0983',	 '9/28/2016',  20	   ,   'FD'	 ,   'E10042');
insert into tblReceiver values('9/25/2016','543791',	'G0983',	 '10/2/2016',  20	   ,   'IP'	 ,   'E10042');
insert into tblReceiver values('10/9/2016','543791',	'G0983',	 '10/12/2016',	20	    ,  'OK'	 ,   'E10042');
insert into tblReceiver values('10/14/2016'	,'543791',	'G0983',	 '10/12/2016',	5	     ,   'OK'	 ,   'E10042');
insert into tblReceiver values('10/19/2016'	,'543791',	'G5698',	 '10/15/2016',	12	    ,  'OK'	 ,   'E10087');
insert into tblReceiver values('10/8/2016','543791',	'T0460',	 '10/12/2016',	100	   ,   'OK' ,	  'E10087');
insert into tblReceiver values('10/9/2016','543791',	'T0460',	 '10/12/2016',	10	    ,  'WD'	 ,   'E10087');
insert into tblReceiver values('10/11/2016'	,'543791',	'T0460',	 '10/12/2016',	10	    ,  'UK'	 ,       null);
insert into tblReceiver values('10/15/2016'	,'600124',	'G0983',	 '10/18/2016',	10	    ,  'WD'	 ,   'E10087');
insert into tblReceiver values('10/16/2016'	,'600124',	'G0983',	 '10/18/2016',	100	   ,   'OK'	 ,   'E10087');
insert into tblReceiver values('10/28/2016'	,'600124',	'G1366',	 '10/18/2016',	150	   ,   'UK'	 ,   'E10087');
insert into tblReceiver values('10/14/2016'	,'600124',	'G5698',	 '10/18/2016',	10	    ,  'UK'	 ,   'E10042');
insert into tblReceiver values('10/16/2016'	,'600124',	'G5698',	 '10/18/2016',	60	    ,  'OK'	 ,   'E10042');
insert into tblReceiver values('10/17/2016'	,'600124',	'G5698',	 '10/18/2016',	30	    ,  'UK'	 ,       null);
insert into tblReceiver values('10/14/2016'	,'902347',	'G0983',	 '10/15/2016',	45	    ,  'UK'	 ,   'E10087');
insert into tblReceiver values('10/15/2016'	,'902347',	'G0983',	 '10/15/2016',	45	    ,  'OK'	 ,   'E10101');
insert into tblReceiver values('10/5/2016','902347',	'G0983',	 '10/15/2016',	10	    ,  'OK'	 ,   'E10101');
insert into tblReceiver values('9/19/2016','902347',	'T0460',	 '9/22/2016',  95	   ,   'OK'	 ,   'E10101');
insert into tblReceiver values('9/24/2016','902347',	'T0460',	 '9/22/2016',  5	    ,  'OK'	 ,   'E10101');
insert into tblReceiver values('9/19/2016','902347',	'T0460',	 '12/5/2016',  100	  ,  'UK'	 ,       null);
insert into tblReceiver values('9/23/2016','112233',	'P7844',	 '9/24/2016',  475.25,	 'OK'	 ,   'E10101');
insert into tblReceiver values('9/28/2016','112233',	'M3577',	 '10/7/2016',  300.45,	 'OK'	 ,   'E10101');
insert into tblReceiver values('10/25/2016'	,'112233',	'M3577',	 '10/7/2016', 340.5	 ,   'WD'	 ,   'E10101');
