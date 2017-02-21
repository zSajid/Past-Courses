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





