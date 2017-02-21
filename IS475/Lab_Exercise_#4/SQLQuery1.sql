select *
from ord;
select * 
from cust;

select *
from ord,cust

select *
from ord, 
	cust
where ord.custID = cust.custID
order by ord.orderid;


select *
from ord
inner join cust
on ord.custID = cust.custID
order by ord.orderID;

select	ord.orderid,
		ord.orderdate, 
		ord.dudedate, 
		cust.customername
from ord
inner join cust
on		ord.custid = cust.custid
order by ord.orderid








