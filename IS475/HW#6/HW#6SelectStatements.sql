/* Problem #1, HW #6*/
select EmpLastName as "Employee Last Name",
	   EmpFirstName as "Employee First Name",
	   EmpPhone as "Employee Phone Number"
from tblEmployee
where EmpEmail is null
order by [Employee Last Name];


/*Problem #2, HW# 6*/
select (EmpLastName + ', ' + substring( EmpFirstName,1,1)+ '.') as "Employee Name", 
		'(' + substring(EmpPhone,1,3)+') ' + substring(EmpPhone,4,3) + '-' + substring(EmpPhone,7,10) as "Employee Phone Number"
from tblEmployee
where EmpEmail is null
order by [EmpLastName];

/*Problem #3 HW #6*

Finish this up*/

select convert(varchar, DateNeeded, 107)  as 'Date Needed' ,
	   ProductID as 'Product Number', 
	   PONumber as 'Purchase Order Number', 
	   QtyOrderered as ' Quantity Ordered', 
	   Price, 
	   convert(decimal(10,2), round((Price * QtyOrderered),2)) as 'Extended Price'
	    
from tblPurchaseOrderLine
where year(dateneeded) = year(GETDATE())
order by [Date Needed] desc; 

/*Problem #4 HW#6 */
select min(price) as 'Least Expensive Selling Price for Product T0460'
from tblPurchaseOrderLine
where ProductID like 'T0460'

/*Problem #5 HW#6*/
select  productID as 'Product Number', 
		description as 'Product Description', 
		EOQ as 'Economic Order Quantity', 
		QOH as 'Quantity on Hand', 
		(QOH - EOQ) as 'Difference',
		case 
			when( (Qoh +50) < EOQ )
				then 'Order Now'
			else
				null	
		end OrderMessage
from tblProduct
where (QOH < EOQ)
order by productID asc

/*Problem #6 HW#6*/
select  productID as 'Product Number', 
		description as 'Product Description', 
		EOQ as 'Economic Order Quantity', 
		QOH as 'Quantity on Hand', 
		(QOH - EOQ) as 'Difference',
		case 
			when( (QOH - EOQ) <= -1 and (QOH -EOQ) >= -5 )
				then null
			
			when( (QOH - EOQ) <= -6 and (QOH - EOQ) >= -10)
				then 'Order next month'

			when( (QOH - EOQ) <= -11 and (QOH - EOQ) >= -35)
				then 'Order next week'

			when((QOH-EOQ) <= -35)
				then 'Order this week'
			when((QOH = 0))
				then 'Order Immediately'
			
		end OrderMessage
from tblProduct
where (QOH < EOQ)
order by EOQ desc

/*Problem #7 HW#6*/
select convert(decimal(10, 3),sum(QtyOrderered * price)) as 'Total Order Price for October'
from tblPurchaseOrderLine
where month(dateneeded) = month(getdate()) and YEAR(DateNeeded) = year(getdate())  ;


/*Problem #8 HW#6*/
select	producttypeid as 'Product Type ID',
		count(*) as 'Count of Products',
		convert(decimal(10, 0), Sum(QOH )) as 'Total Quantity on Hand',
		convert(decimal(10, 2), sum(qoh)/count(*)) as 'Average Quantity on Hand'
from tblProduct
group by ProductTypeID

/*Problem #9 HW #6*/
select	ProductTypeID as 'Product Type ID', 
		count(*) as 'Counts of Products', 
		convert(decimal(10, 0), sum(qoh)) as 'Total Quantity on Hand',
		convert(decimal(10, 2), sum(qoh)/count(*)) as 'Average Quantity on Hand'
from tblProduct
group by ProductTypeID
having convert(decimal(10, 2), sum(qoh)/count(*)) > 50;

/*Problem #10 HW #6*/
select	productID as 'Product Number',
		convert(varchar, max(datepurchased), 101) as 'Last Date Purchased',
		count(*) as 'Number of Times Purchased',
		min(price) as 'Minimum Purchase Price', 
		max(price) as 'Maximum Purchase Price', 
		(max(price) - min(price)) as 'Difference between Maximum and minimum Price'
from tblPurchaseHistory
group by ProductID

/*Problem #11 HW#6*/
select productID as 'Product Number',
		convert(varchar, max(datepurchased), 101) as 'Last Date Purchased',
		count(*) as 'Number of Times Purchased',
		min(price) as 'Minimum Purchase Price', 
		max(price) as 'Maximum Purchase Price', 
		(max(price) - min(price)) as 'Difference between Maximum and minimum Price'
from tblPurchaseHistory
group by ProductID
having (max(price) -min(price)) = 0

/*Problem #12 HW #6 FINISH*/

/*Problem #13 HW #6*/
select	convert(varchar,PODateNeeded,107) as 'Date Needed', 
		convert(varchar, GetDate(), 107) as 'Today''s Date',
		abs((convert(int, podateneeded, 107)- convert(int, getdate(), 107))) as 'Days Overdue',
		PoNumber as 'Purchase Order Number',
		convert(varchar, PODatePlaced, 107) as 'Date Ordered', 
		BuyerEmpID as 'Buyer',
		VendorID as 'Vendor ID'
from tblPurchaseOrder
where DATEDIFF(day, podateneeded, getdate()) > 7
order by PODateNeeded

/*Problem #14 HW#6*/
select	vendorid as 'Vendor Number',
		name as 'Vendor Name', 
		zip as 'Vendor Zip Code', 
		FirstBuyDate as 'Date First Purchased'
from tblVendor
where FirstBuyDate = (select min(FirstBuyDate) from tblVendor);

/*Problem #15 HW#6*/
select	PoNumber as 'Purchase Order Number',
		 convert(varchar, PODatePlaced, 107) as 'Date Purchase Order Placed',
		 convert(varchar, PODateNeeded, 107) as 'Date Needed',
		 terms as 'Terms',
		 VendorId 
from tblPurchaseOrder
where VendorID = (	select VendorID as 'Vendor Number' 
					from tblVendor);





