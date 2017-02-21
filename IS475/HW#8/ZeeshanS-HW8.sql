/*Use the database zsajid to test out this code*/
/*Code for the views are at the bottom*/

/*Query #1*/
select	poline.ponumber 'Purchase Order Number',
		convert(varchar, max(po.PODatePlaced), 107)  as 'PO Date',
		ven.Name as 'Vendor Name', 
		isnull(tblemp.EmpLastName + '. ' + substring(tblEmp.EmpFirstName,1,1), 'No Employee') as 'Employee Buyer',
		case
			when tblManager.EmpID is null
				then 'No Manager on File'
			else tblManager.EmpLastName + '. ' + substring( tblManager.EmpFirstName,1,1) 
			end 'Manager of Buyer',
		poline.ProductID as 'Product ID', 
		prod.Description as 'Product Description', 
		convert(varchar, max(poline.DateNeeded ), 107) as 'Date Needed', 
		poline.Price as 'Product Price', 
		qtyordered as 'Quantity Ordered', 
		convert(decimal(8, 2), isnull(sum(qtyreceived),0)) 'Quantity Received',
		isNull(qtyordered, 0) - isnull(sum(qtyreceived),0) 'Quantity Remaining', 
		case 
			when ((isNull(qtyordered, 0) - isnull(sum(qtyreceived),0)) =  qtyordered)
				then 'Not Received'
			when( isNull(qtyordered, 0) - isnull(sum(qtyreceived),0)) = 0
				then 'Complete'
			when (isNull(qtyordered, 0) - isnull(sum(qtyreceived),0) < 0)
				then 'Over Shipped'
			when (isNull(qtyordered, 0) - isnull(sum(qtyreceived),0) >0)
				then 'Partially Received'
	
			else
				null
			end 'Receiving Status'
from tblPurchaseOrderLine poline
left outer join tblreceiver rec
	on poline.PONumber = rec.ponumber
	and poline.ProductID = rec.productID
	and poline.dateneeded = rec.dateneeded
inner join tblProduct prod
	on poline.ProductID = prod.ProductID
inner join tblPurchaseOrder po
	on po.PoNumber = poline.PONumber
inner join tblVendor ven
	on ven.VendorID = po.VendorID
left outer join tblEmployee tblEmp
	on po.BuyerEmpID = tblEmp.EmpID
left outer join tblEmployee tblManager
	on tblEmp.EmpMgrID = tblManager.EmpID
group by	poline.PONumber,
			po.PODatePlaced,
			ven.Name,
			poline.ProductID,
			poline.DateNeeded,
			poline.Price,
			prod.Description,
			poline.qtyordered,
			tblemp.EmpLastName,
			tblEmp.EmpFirstName,
			tblManager.EmpFirstName,
			tblManager.EmpLastName,
			tblManager.EmpID


/*Query #2*/
select	tblPO.PONumber 'PONumber',
		convert(varchar, max(tblPO.PODatePlaced), 107)  'PODatePlaced',
		convert(varchar, max(tblPO.PODateNeeded), 107)  'PODateNeeded', 
		ven.Name 'VendorName'
from tblPurchaseOrderLine
inner join tblPurchaseOrder tblPO
	on tblPurchaseOrderLine.PONumber = tblPO.ponumber
inner join tblVendor ven
	on ven.VendorID = tblPO.VendorID
left join vOpenOrders vOO
	on tblPO.ponumber = vOO.ponumber
where vOO.ponumber is null
group by tblPO.PONumber ,
			ven.Name

/* Query #3*/
select	tblPO.PONumber 'PONumber',
		convert(varchar, max(tblPO.PODatePlaced), 107)  'PODatePlaced',
		convert(varchar, max(tblPO.PODateNeeded), 107)  'PODateNeeded', 
		ven.Name 'VendorName'
from tblPurchaseOrderLine
inner join tblPurchaseOrder tblPO
	on tblPurchaseOrderLine.PONumber = tblPO.ponumber
inner join tblVendor ven
	on ven.VendorID = tblPO.VendorID
left join vOpenOrders vOO
	on tblPO.ponumber = vOO.ponumber
where vOO.ponumber is not null
group by tblPO.PONumber ,
			ven.Name

/*Query #4 Finish This*/
select	poline.PONumber 'PO Number',
		vtor.podate 'PO Date',
		vtor.venname 'Vendor Name',
		vTOR.EmployeeBuyer 'Employee Buyer',
		vtor.Manager 'Manager of Buyer',
		vtor.pid 'Product ID',
		vtor.productdescription 'Product Description',
		vtor.dateneeded 'Date Needed',
		vtor.PPrice 'Product Price',
		vtor.QOrder 'Quantity Ordered',
		vtor.qreceived 'Quantity Received',
		vtor.qremaining 'Quantity Remaining',
		vtor.RStatus 'Receiving Status'
from tblPurchaseOrderLine poline
left  join vOpenOrders vOO
	on poline.ponumber = vOO.ponumber
left join vTotalOrdersReceived vTOR
	on vTOR.ponumber = vOO.ponumber
left join tblVendor ven
	on ven.vendorid = poline.productid
where vOO.ponumber is not null
group by poline.PONumber ,
		vtor.podate,
		vtor.venname,
		vTOR.EmployeeBuyer,
		vtor.pid,
		vtor.productdescription,
		vtor.dateneeded,
		vtor.PPrice,
		vtor.QOrder,
		vtor.qreceived,
		vtor.qremaining,
		vtor.RStatus,
		vtor.Manager


/*Query #5 */
select	poline.PONumber 'PO Number',
		convert(varchar, tblPO.podateplaced, 107) 'PO Date',
		convert(varchar, tblPO.podateneeded,107) 'Date Needed',
		vtor.venname 'Vendor Name',
		vtor.pid 'Product ID',		
		convert(varchar, min(rec.datereceived), 107) FirstDateReceived,
		convert(varchar, max(rec.datereceived), 107) LastDateReceived,
		vtor.QOrder 'Quantity Ordered',
		vtor.QReceived 'Quantity Remaining'
from tblPurchaseOrderLine poline
left join tblreceiver rec
	on rec.productID = poline.productID 
left join vOpenOrders vOO
	on poline.ponumber = vOO.ponumber
left join vTotalOrdersReceived vTOR
	on vTOR.ponumber = poline.ponumber
left join tblpurchaseorder tblPO
	on tblPO.ponumber = poline.ponumber
where vOO.ponumber is  null
group by poline.PONumber ,
		tblPO.podateplaced  ,
		tblPO.podateneeded ,
		vtor.venname ,
		vtor.pid ,
		vtor.QOrder ,
		vtor.QReceived,
		tblPO.ponumber



		
/* Query #6*/
select	historical_price.productid,
		historical_price.description,
		historical_price.purchasePrice    RecentHistoricalPrice,
		max(tblPOL.Price) as currentPrice,
		tblPOL.PONumber 'PONumber',
		ven.Name VendorName
from  historical_price 
inner join tblPurchaseOrderLine tblPOL
	on historical_price.productid = tblPOL.productid
inner join tblPurchaseOrder tblPO
	on tblPO.PoNumber = tblPOL.PONumber
inner join tblVendor ven
	on ven.VendorID = tblPO.VendorID
where ((tblPOL.productid = historical_price.productid) and (tblPOL.Price > (historical_price.purchasePrice + (historical_price.purchasePrice*.10))))  
											
group by historical_price.productid,
		 historical_price.description,
		 historical_price.purchasePrice ,
		 tblPOL.PONumber,
		 ven.Name
order by tblPOL.PONumber


/*Query #7*/
select	top 1(ven.VendorID) as 'vendor ID',
		ven.Name as 'vendor Name',
		ven.Email as 'vendor Email Address',
		count(*) as  'Count of Over-Shipped Purchase Order Lines'
from tblVendor ven
left outer join vReceivedShipment
	on vReceivedShipment.name = ven.name
where  (vReceivedShipment.ReceivingStatus = 'Over Shipped' and vReceivedShipment.name = ven.name ) 
group by ven.vendorid,
		 ven.name, 
		 ven.email,
		 vReceivedShipment.name
order by  count(*) desc

/* Query #8 */
select	top 1 tblE.empid EmployeeID,
		tblE.emplastname + ', ' + substring(tble.empfirstname, 1,1) as 'Employee''s Name',
		tblE.empemail as 'Employee''s Email', 
		tblE.empmgrid as 'Manager EmpID',
		tblM.empemail as 'Manager''s Email', 
		sum(rec.qtyreceived) as 'Quantity of Damaged Items Received'
from tblemployee tblE
inner join tblreceiver rec
	on rec.receiveempid = tblE.empid
inner join tblemployee tblM
	on tble.empmgrid = tblM.empid
inner join tblcondition tblC
	on rec.conditionID = tblC.conditionID
where tblC.description like '%damage%'
group by tblE.empid,
		tblE.emplastname,
		tble.empfirstname,
		tblE.empemail , 
		tblE.empmgrid ,
		tblM.empemail 
order by sum(rec.qtyreceived) desc


/*Query #9 */
select	tblP.productID 'Product ID', 
		tblP.description 'Product Description', 
		tblPTT.description 'Product Type Description',
		isnull(sum(tblPOL.qtyordered),0)  'Total Qty Currently on Order',
		isnull(max(tblPOL.price),0) 'Current Most Expensive Price', 
		isnull(min(tblPOl.price),0) 'Current Least Expensive Price',
		isnull(avg(tblPOL.price),0) 'Current Average Price',
		isnull(max(tblPH.price), 0) 'Past Most Expensive Price',
		isnull(min(tblPH.price), 0) 'Past Least Expensive Price',
		isnull(avg(tblPH.price), 0.00) 'Past Average Price',
		historical_price.recentDate 'Most Recent Purchase Date', 
		isnull(historical_price.purchasePrice,0.00) 'Most Recent Purchase Price'
from tblproduct tblP
left outer join tblproducttype tblPTT
	on tblPTT.producttypeid = tblp.producttypeid
left outer join tblpurchaseorderline tblPOL
	on tblPOL.productid = tblP.productID 
left outer join tblpurchaseorder tblPO
	on tblPO.ponumber = tblPOL.ponumber
left outer join historical_price
	on historical_price.productID = tblP.productID
left outer join tblpurchasehistory tblPH
	on tblPH.productID = tblP.productID
group by	tblP.productID, 
			tblP.description, 
			tblPTT.description,
			historical_price.recentDate,
			historical_price.purchasePrice
order by tblP.productID

/* Query #10*/
select	top 1 tblP.productID 'Product ID', 
		tblP.description 'Product Description', 
		tblPOL.ponumber 'PO Number',
		tblPO.podateplaced 'Date of Purchase Order',
		ven.name 'Vendor Name',
		isnull(max(tblPOL.price),0) 'Current Most Expensive Price',  
		historical_price.purchasePrice 'Most Recent Purchase Price',
		max(tblPOL.price) - historical_price.purchasePrice 'Price Difference',
		(convert(varchar, ((max(tblPOL.price) - historical_price.purchasePrice)/historical_price.purchasePrice)* 100,5))+ '%'
from tblproduct tblP
left outer join tblpurchaseorderline tblPOL
	on tblPOL.productid = tblP.productID 
left outer join tblpurchaseorder tblPO
	on tblPO.ponumber = tblPOL.ponumber
inner join historical_price
	on historical_price.productID = tblP.productID
inner join tblpurchasehistory tblPH
	on tblPH.productID = tblP.productID
left outer join tblVendor ven
	on tblPH.vendorID = ven.vendorid
group by	tblP.productID, 
			tblP.description, 
			historical_price.recentDate,
			historical_price.purchasePrice,
			tblPOL.ponumber,
			tblPO.podateplaced, 
			ven.name
order by  (max(tblPOL.price) - historical_price.purchasePrice)/historical_price.purchasePrice desc


/*Views Code*/
create view vTotalOrdersReceived as
select	poline.ponumber ponumber,
		convert(varchar, max(po.PODatePlaced), 107)  as PODate,
		ven.Name as venName, 
		tblemp.EmpLastName + '. ' + substring(tblEmp.EmpFirstName,1,1) as EmployeeBuyer,
		case
			when tblManager.EmpID is null
				then 'No Manager on File'
			else tblManager.EmpLastName + '. ' + substring( tblManager.EmpFirstName,1,1) 
			end Manager,
		poline.ProductID as PID, 
		prod.Description as ProductDescription, 
		convert(varchar, max(poline.DateNeeded ), 107) as DateNeeded, 
		poline.Price as PPrice, 
		qtyordered as QOrder, 
		convert(decimal(8, 2), isnull(sum(qtyreceived),0)) QReceived,
		isNull(qtyordered, 0) - isnull(sum(qtyreceived),0) QRemaining, 
		case 
			when ((isNull(qtyordered, 0) - isnull(sum(qtyreceived),0)) =  qtyordered)
				then 'Not Received'
			when( isNull(qtyordered, 0) - isnull(sum(qtyreceived),0)) = 0
				then 'Complete'
			when (isNull(qtyordered, 0) - isnull(sum(qtyreceived),0) < 0)
				then 'Over Shipped'
			when (isNull(qtyordered, 0) - isnull(sum(qtyreceived),0) >0)
				then 'Partially Received'
	
			else
				null
			end RStatus
from tblPurchaseOrderLine poline
left outer join tblreceiver rec
	on poline.PONumber = rec.ponumber
	and poline.ProductID = rec.productID
	and poline.dateneeded = rec.dateneeded
inner join tblProduct prod
	on poline.ProductID = prod.ProductID
inner join tblPurchaseOrder po
	on po.PoNumber = poline.PONumber
inner join tblVendor ven
	on ven.VendorID = po.VendorID
left outer join tblEmployee tblEmp
	on po.BuyerEmpID = tblEmp.EmpID
left outer join tblEmployee tblManager
	on tblEmp.EmpMgrID = tblManager.EmpID
group by	poline.PONumber,
			po.PODatePlaced,
			ven.Name,
			poline.ProductID,
			poline.DateNeeded,
			poline.Price,
			prod.Description,
			poline.qtyordered,
			tblemp.EmpLastName,
			tblEmp.EmpFirstName,
			tblManager.EmpFirstName,
			tblManager.EmpLastName,
			tblManager.EmpID

select *
from vTotalOrdersReceived

drop view vTotalOrdersReceived

/*View 2
Second view to check what orders are actually open*/
create view vOpenOrders as

select	distinct (poline.ponumber),
		poline.productid,
		poline.dateneeded,
		poline.qtyordered,
		allorders.QReceived
from tblpurchaseorderline poline
left join tblreceiver rec
	on poline.productid = rec.productID and
	   poline.ponumber = rec.ponumber 
left join vTotalOrdersReceived allOrders
	on allorders.ponumber = poline.ponumber and
	allorders.pid = poline. productid 
where allorders.QReceived < poline.qtyordered

select *
from vOpenOrders

drop view vopenorders

/*View 3*/
create view historical_price as 
select	prod.productID productID,
		prod.Description description, 
		prod.EOQ eoq,
		isnull(convert(varchar, tblPH.DatePurchased,107), 'Not in Previous Purchase') recentDate,
		isnull(convert(varchar, tblph.Qty, 101), '--') quantityPurchased, 
		tblph.price purchasePrice 
from tblProduct as prod
full outer  join tblPurchaseHistory as tblPH
	on prod.ProductID = tblPH.ProductID
where tblPH.DatePurchased = (select Max(tblPurchaseHistory.DatePurchased)
							from tblPurchaseHistory
							where tblPurchaseHistory.ProductID = prod.ProductID) or tblPH.DatePurchased is null
order by prod.ProductID

select *
from historical_price

drop view historical_price

/*View 3*/
create view vReceivedShipment as
select	poline.ponumber 'Purchase Order Number',
		convert(varchar, max(po.PODatePlaced), 107)  as 'PO Date',
		ven.Name as Name, 
		tblemp.EmpLastName + '. ' + substring(tblEmp.EmpFirstName,1,1) as 'Employee Buyer',
		case
			when tblManager.EmpID is null
				then 'No Manager on File'
			else tblManager.EmpLastName + '. ' + substring( tblManager.EmpFirstName,1,1) 
			end 'Manager of Buyer',
		poline.ProductID as 'Product ID', 
		prod.Description as 'Product Description', 
		convert(varchar, max(poline.DateNeeded ), 107) as 'Date Needed', 
		poline.Price as 'Product Price', 
		qtyordered as 'Quantity Ordered', 
		convert(decimal(8, 2), isnull(sum(qtyreceived),0)) 'Quantity Received',
		isNull(qtyordered, 0) - isnull(sum(qtyreceived),0) 'Quantity Remaining', 
		case 
			when ((isNull(qtyordered, 0) - isnull(sum(qtyreceived),0)) =  qtyordered)
				then 'Not Received'
			when( isNull(qtyordered, 0) - isnull(sum(qtyreceived),0)) = 0
				then 'Complete'
			when (isNull(qtyordered, 0) - isnull(sum(qtyreceived),0) < 0)
				then 'Over Shipped'
			when (isNull(qtyordered, 0) - isnull(sum(qtyreceived),0) >0)
				then 'Partially Received'
	
			else
				null
			end ReceivingStatus
from tblPurchaseOrderLine poline
left outer join tblreceiver rec
	on poline.PONumber = rec.ponumber
	and poline.ProductID = rec.productID
	and poline.dateneeded = rec.dateneeded
inner join tblProduct prod
	on poline.ProductID = prod.ProductID
inner join tblPurchaseOrder po
	on po.PoNumber = poline.PONumber
inner join tblVendor ven
	on ven.VendorID = po.VendorID
left outer join tblEmployee tblEmp
	on po.BuyerEmpID = tblEmp.EmpID
left outer join tblEmployee tblManager
	on tblEmp.EmpMgrID = tblManager.EmpID
group by	poline.PONumber,
			po.PODatePlaced,
			ven.Name,
			poline.ProductID,
			poline.DateNeeded,
			poline.Price,
			prod.Description,
			poline.qtyordered,
			tblemp.EmpLastName,
			tblEmp.EmpFirstName,
			tblManager.EmpFirstName,
			tblManager.EmpLastName,
			tblManager.EmpID

select * 
from vReceivedShipment

drop view vReceivedShipment





