select	cust.customername,
		isnull(ord.orderID, 'No Order') orderID,
		ord.duedate
from	ord
inner join cust
on		ord.custid = cust.custId
order by cust.customername

select	cust.customername,
		isnull(ord.orderID, 'No Order') orderID,
		ord.duedate
from	ord
right outer join cust
on		ord.custid = cust.custId
order by cust.customername 

select	cust.customername,
		isnull(ord.orderID, 'No Order') orderID,
		ord.duedate
from	cust
right outer join ord
on		ord.custid = cust.custId
order by cust.customername 

select	*
from	ord2 
inner join cust
on ord2.custid = cust.custid

select *
from ord2
left outer join cust
on ord2.custid = cust.custid

select	orderid, 
		orderdate, 
		ord2.custid, 
		duedate, 
		isnull(cust.custid, 'n/a') custid, 
		isnull(cust.customername, 'Missing Name') customername
from ord2
left outer join cust
on ord2.custid = cust.custid;

select *
from ord2
full outer join cust
on ord2.custid = cust.custid



select *
from ord3
inner join cust
on ord3.custid = cust.custid
inner join emp3
on ord3.empid = emp3.empid

select *
from ord3
left outer join cust
on ord3.custid = cust.custid
inner join emp3
on ord3.empid = emp3.empid
