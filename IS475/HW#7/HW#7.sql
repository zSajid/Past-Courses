/*Query #1 Done*/
select	convert(varchar, tblPurchaseOrder.PODateNeeded, 107) as 'Date of Required Delivery',
		tblPurchaseOrder.PONumber as 'Purchase Order Number',
		convert(varchar, tblPurchaseOrder.PODatePlaced, 107)  as 'Date of Purchase Order', 
		tblVendor.Name as 'Vendor Name',
		'(' + substring(tblVendor.Phone,1,3)+') ' + substring(tblVendor.Phone,4,3) + '-' + substring(tblVendor.Phone,7,10) as 'Vendor Phone Number' , 
		tblPurchaseOrder.BuyerEmpID as 'Buyer ID'
from tblPurchaseOrder
inner join tblVendor
on tblPurchaseOrder.VendorID = tblVendor.VendorID
where month( tblPurchaseOrder.PODateNeeded) = 10 or month(tblpurchaseorder.podateneeded) = 11 and YEAR( tblPurchaseOrder.PODateNeeded) = year(getdate())
order by (tblpurchaseorder.podateneeded) desc;

/*Query #2 Done */
select	convert(varchar, tblPurchaseOrder.PODateNeeded, 107) as 'Date of Required Delivery',
		tblPurchaseOrder.PONumber as 'Purchase Order Number',
		convert(varchar, tblPurchaseOrder.PODatePlaced, 107)  as 'Date of Purchase Order', 
		tblVendor.Name as 'Vendor Name',
		'(' + substring(tblVendor.Phone,1,3)+') ' + substring(tblVendor.Phone,4,3) + '-' + substring(tblVendor.Phone,7,10) as 'Vendor Phone Number' , 
		isnull(tblEmployee.EmpFirstName + tblEmployee.EmpLastName, 'No Buyer') as 'Buyer Name'
from tblPurchaseOrder
inner join tblVendor
on tblPurchaseOrder.VendorID = tblVendor.VendorID
full outer join tblEmployee 
on tblEmployee.EmpID = tblPurchaseOrder.BuyerEmpID
where month( tblPurchaseOrder.PODateNeeded) = 10 or month(tblpurchaseorder.podateneeded) = 11 and YEAR( tblPurchaseOrder.PODateNeeded) = year(getdate())
order by (tblpurchaseorder.podateneeded) desc;

/*Query #3 Done*/
select	convert(varchar, tblPurchaseOrder.PODateNeeded, 107) as 'Date of Required Delivery',
		tblPurchaseOrder.PONumber as 'Purchase Order Number',
		convert(varchar, tblPurchaseOrder.PODatePlaced, 107)  as 'Date of Purchase Order', 
		tblVendor.Name as 'Vendor Name',
		'(' + substring(tblVendor.Phone,1,3)+') ' + substring(tblVendor.Phone,4,3) + '-' + substring(tblVendor.Phone,7,10) as 'Vendor Phone Number' , 
		isnull(tblEmployee.EmpFirstName + ' ' +  tblEmployee.EmpLastName, 'No Buyer') as 'Buyer Name',
		isnull(manager.empfirstname + ' ' + manager.EmpLastName, 'No Manager') as 'Manager Name'		
from  tblPurchaseOrder
inner join tblVendor
on tblPurchaseOrder.VendorID = tblVendor.VendorID
full outer join tblEmployee 
on tblEmployee.EmpID = tblPurchaseOrder.BuyerEmpID
left outer join tblEmployee as manager 
on tblEmployee.empmgrid = manager.EmpID
where month( tblPurchaseOrder.PODateNeeded) = 10 or month(tblpurchaseorder.podateneeded) = 11 and YEAR( tblPurchaseOrder.PODateNeeded) = year(getdate())
order by (tblpurchaseorder.podateneeded) desc;

/*Query #4, Done */
select	 tblPurchaseOrder.ponumber as 'Purchase Order Number', 
		tblPurchaseOrder.PODatePlaced as ' Date of Purchase Order Placed', 
		tblPurchaseOrder.PODateNeeded as 'Date Needed', 
		tblPurchaseOrder.Terms as 'Terms',
		tblPurchaseOrder.VendorID as 'Vendor Number', 
		tbv.Name as 'Vendor Name'
from tblPurchaseOrder
inner join tblVendor tbv
on tblPurchaseOrder.VendorID = tbv.VendorID
where not exists(select tblreceiver.ponumber
			from tblreceiver
			where ((tblPurchaseOrder.PoNumber = tblreceiver.PoNumber)));

/*Query #5 Done */	
select	tblProduct.ProductID as 'Product ID', 
		tblProduct.Description as 'Product Description', 
		tblProductType.Description as 'Product Type', 
		tblProduct.UOM as 'Unit of Measure', 
		tblProduct.QOH as ' Quantity on Hand'
from tblProduct
inner join tblProductType
	on tblProductType.ProducttypeID = tblProduct.ProductTypeID
where not exists(select tblProduct.ProductID
			from tblPurchaseOrderLine
			where ((tblProduct.ProductID = tblPurchaseOrderLine.ProductID)));

/*Query 6 Finish This*/
select	ponumber,
		tblProduct.ProductID as 'productid',
		tblProduct.Description as 'description',
		max(tblPurchaseOrderLine.Price) as price
from tblPurchaseOrderLine
left join tblProduct
	on tblProduct.ProductID = tblPurchaseOrderLine.ProductID
where tblProduct.Description = 'Alpine Small Pot'
group by PONumber, tblProduct.ProductID, tblProduct.Description;


/*Query 7 Done*/
select	tblreceiver.productID as 'Product ID',
		convert(varchar,	tblreceiver.datereceived, 107) as 'Date Product Receieved', 
		tblreceiver.ponumber as 'Purchase Order Number', 
		tblreceiver.qtyreceived as 'Quantity Receieved', 
		tblCondition.Description as 'Condition Receieved' 
from tblreceiver
inner join tblCondition
	on tblCondition.ConditionID = tblreceiver.conditionID
where tblreceiver.conditionID != 'OK' and tblreceiver.conditionID != 'IP' and tblreceiver.conditionID != 'OT' and tblreceiver.conditionID != 'UK'
order by tblreceiver.productID asc, tblreceiver.datereceived	asc

/*Query 8 Finish Done*/
select	tblreceiver.productID as 'Product ID',
		tblProduct.Description as 'Product Description', 
		tblProductType.Description as 'Product Type Description', 
		convert(varchar,	tblreceiver.datereceived, 107) as 'Date Product Receieved', 
		tblreceiver.ponumber as 'Purchase Order Number', 
		tblreceiver.qtyreceived as 'Quantity Receieved', 
		tblCondition.Description as 'Condition Receieved' 
from tblreceiver
inner join tblCondition
	on tblCondition.ConditionID = tblreceiver.conditionID
inner join tblProduct
	on tblreceiver.productID = tblProduct.ProductID
inner join tblProductType
	on tblProduct.ProductTypeID = tblProductType.ProducttypeID
where tblreceiver.conditionID != 'OK' and tblreceiver.conditionID != 'IP' and tblreceiver.conditionID != 'OT' and tblreceiver.conditionID != 'UK'
order by tblreceiver.productID asc, tblreceiver.datereceived	asc

/*Query 9 Done*/
select	tblreceiver.productID as 'Product ID',
		tblProduct.Description as 'Product Description', 
		tblProductType.Description as 'Product Type Description', 
		convert(varchar,	tblreceiver.datereceived, 107) as 'Date Product Receieved', 
		tblreceiver.ponumber as 'Purchase Order Number', 
		tblVendor.name as 'Vendor Name', 
		'(' + substring(tblVendor.Phone,1,3)+') ' + substring(tblVendor.Phone,4,3) + '-' + substring(tblVendor.Phone,7,10)  as 'Vendor Phone Number',
		tblreceiver.qtyreceived as 'Quantity Receieved', 
		tblCondition.Description as 'Condition Receieved' 
from tblreceiver
inner join tblCondition
	on tblCondition.ConditionID = tblreceiver.conditionID
inner join tblProduct
	on tblreceiver.productID = tblProduct.ProductID
inner join tblProductType
	on tblProduct.ProductTypeID = tblProductType.ProducttypeID
inner join tblPurchaseOrder	
	on tblPurchaseOrder.PoNumber = tblreceiver.PoNumber
inner join tblVendor
	on tblVendor.VendorID = tblPurchaseOrder.VendorID
where tblreceiver.conditionID != 'OK' and tblreceiver.conditionID != 'IP' and tblreceiver.conditionID != 'OT' and tblreceiver.conditionID != 'UK'
order by tblreceiver.productID asc, tblreceiver.datereceived	asc

/*Query 10 Done*/
select	distinct tblVendor.name as 'Vendor Name', 
		'(' + substring(tblVendor.Phone,1,3)+') ' + substring(tblVendor.Phone,4,3) + '-' + substring(tblVendor.Phone,7,10)  as 'Vendor Phone Number'
from tblreceiver
inner join tblProduct
	on tblreceiver.productID = tblProduct.ProductID
inner join tblPurchaseOrder	
	on tblPurchaseOrder.PoNumber = tblreceiver.PoNumber
inner join tblVendor
	on tblVendor.VendorID = tblPurchaseOrder.VendorID 
where tblreceiver.conditionID != 'OK' and tblreceiver.conditionID != 'IP' and tblreceiver.conditionID != 'OT' and tblreceiver.conditionID != 'UK' and tblProduct.Description = 'Alpine Small Pot'


/*Query 11 Finish this*/
select	tblProduct.ProductID as productid,
		tblProduct.Description as 'description',
		count(*) as 'Number of Purchase Orders',
		case 
			when (tblPol.QtyOrderered) > 0
				then(tblPOL.QtyOrderered) 
			else	
				0	
			end as 'Total Quantity Ordered',
		case 
			when (max(tblPOL.Price)) > 0
					then(max(tblPol.price))
			else
				0
			end  as 'Maximum Price Paid', 
		case 
			when (min(tblPOL.Price)) > 0
					then(min(tblPOL.Price))
			else
				0
			end   as 'Minimum Price Paid', 
		case 
			when (avg(tblPOL.price)) > 0
					then(avg(tblPOL.price))
			else
				0
			end    as' Average Price Paid'
from  tblProduct
left outer join tblPurchaseOrderLine tblPOL
	on tblPOL.ProductID = tblProduct.ProductID
group by tblProduct.ProductID, tblProduct.Description, tblPOL.QtyOrderered, tblpol.ProductID
order by tblProduct.ProductID

/*Query 12*/
select	tblProduct.ProductID as 'Product ID',
		tblProduct.Description as 'Product Description',
		tblProduct.EOQ as 'Product Economic Order Quantity', 
		convert(varchar,tblPurchaseHistory.DatePurchased, 107) as 'Most Recent Purchase Date',
		tblPurchaseHistory.Qty as 'Quantity Purchased', 
		tblPurchaseHistory.Price as 'Purchase Price'
from tblProduct
inner join tblPurchaseHistory
	on tblPurchaseHistory.ProductID = tblProduct.ProductID

/*Query 13 Done*/
select	tblPurchaseOrder.PoNumber as 'Purchase Order Number', 
		convert(varchar,tblPurchaseOrder.PODatePlaced, 107) as 'Date of Purchase Order',
		tblVendor.Name as 'Vendor Name', 
		tblPurchaseOrder.BuyerEmpID as 'Buyer', 
		tblPurchaseOrderLine.ProductID as 'Product ID', 
		tblProduct.Description as 'Product Description',
		convert(varchar,	tblPurchaseOrder.PODateNeeded , 107) as 'Product Date Needed', 
		tblPurchaseOrderLine.qtyordered as 'Quantity Ordered', 
		tblPurchaseOrderLine.Price as 'Unit Price', 
		convert(decimal(10, 2),(tblPurchaseOrderLine.qtyordered * tblPurchaseOrderLine.price)) as 'Extended Price'
from tblPurchaseOrder
inner join tblPurchaseOrderLine
	on tblPurchaseOrderLine.PONumber = tblPurchaseOrder.PoNumber
right outer join tblVendor
	on tblVendor.VendorID = tblPurchaseOrder.VendorID
inner join tblProduct
	on tblPurchaseOrderLine.ProductID = tblProduct.ProductID

/*Query 14 Finish This up asap*/
select	tblPurchaseOrder.PoNumber as 'Purchase Order Number', 
		convert(varchar,tblPurchaseOrder.PODatePlaced, 107) as 'Date of Purchase Order',
		tblVendor.Name as 'Vendor Name', 
		tblPurchaseOrder.BuyerEmpID as 'Buyer', 
		tblPurchaseOrderLine.ProductID as 'Product ID', 
		tblProduct.Description as 'Product Description',
		tblPurchaseOrder.PODateNeeded as 'Product Date Needed', 
		tblPurchaseOrderLine.QtyOrderered as 'Quantity Ordered',
		tblreceiver.datereceived as 'Date Product Received', 
		tblreceiver.qtyreceived as 'Quantity Received'
from tblPurchaseOrder
inner join tblPurchaseOrderLine
	on tblPurchaseOrderLine.PONumber = tblPurchaseOrder.PoNumber
right outer join tblVendor
	on tblVendor.VendorID = tblPurchaseOrder.VendorID
inner join tblProduct
	on tblPurchaseOrderLine.ProductID = tblProduct.ProductID
inner join tblreceiver
	on tblPurchaseOrderLine.ProductID =tblreceiver.productID
order by tblPurchaseOrder.PoNumber, tblreceiver.qtyreceived

/*Query 15 Finish this up asap*/
select	tblPurchaseOrder.PoNumber as 'Purchase Order Number', 
		convert(varchar,tblPurchaseOrder.PODatePlaced, 107) as 'Date of Purchase Order',
		tblVendor.Name as 'Vendor Name', 
		tblPurchaseOrder.BuyerEmpID as 'Buyer', 
		tblPurchaseOrderLine.ProductID as 'Product ID', 
		tblProduct.Description as 'Product Description',
		tblPurchaseOrder.PODateNeeded as 'Product Date Needed', 
		tblPurchaseOrderLine.QtyOrderered as 'Quantity Ordered',
		tblreceiver.qtyreceived as 'Total Quantity Receieved', 
		(tblPurchaseOrderLine.QtyOrderered - tblreceiver.qtyreceived) as 'Quantity Remaining to be Receieved'

from tblPurchaseOrder
inner join tblPurchaseOrderLine
	on tblPurchaseOrderLine.PONumber = tblPurchaseOrder.PoNumber
right outer join tblVendor
	on tblVendor.VendorID = tblPurchaseOrder.VendorID
inner join tblProduct
	on tblPurchaseOrderLine.ProductID = tblProduct.ProductID
inner join tblreceiver
	on tblPurchaseOrderLine.ProductID =tblreceiver.productID
order by tblPurchaseOrder.PoNumber, tblreceiver.qtyreceived
