select *
from vempdata

select	ord.orderid,
		ord.orderdate, 
		ord.empid, 
		v.employeename,
		v.title,
		v.managername
from ord
left outer join vempdata v
on ord.empid = v.empid

create view vavgrate as 
select	jobtitleid, 
		avg(payrate) AveragePayRate
from emp
group by jobtitleid;


select *
from vavgrate

select	emp.empid,
		emp.empname, 
		emp.payrate, 
		emp.jobtitleid,
		title, 
		vavgrate.AveragePayRate
from emp
left outer join vavgrate
on emp.jobtitleid = vavgrate.jobtitleid
left outer join jobtitle jt
on jt.jobtitleid = emp.jobtitleid
where payrate > AveragePayRate

create view vcustordarmount as
select	custid, 
		sum(orderamount) custamount
from ord
group by custid

select	v.custid, 
		cust.CustomerName,
		v.custamount
from vcustordarmount v
inner join cust
on v.CustID = cust.CustID
where custamount = 
	(select max(custamount)
	from vcustordarmount)


select	v.custid, 
		cust.CustomerName,
		v.custamount
from vcustordarmount v
left outer join cust
on v.CustID = cust.CustID
where custamount = 
	(select min(custamount)
	from vcustordarmount)

select empid, 
		month(orderdate) monthorderdate, 
		year(orderdate) yearorderdate, 
		count(*) ordercount 
from ord
group by empid, month(orderdate), year(orderdate)


create view vemporders as 
select	empid, 
		month (orderdate) MonthorderDate, 
		year(orderdate) YearOrderDate, 
		count(*) Ordercount
from ord
group by empid, 
		 month(orderdate),
		year(orderdate)


create view voctoberemporders as
select *
from vemporders
where MonthorderDate =10 and YearOrderDate = year(getdate())

select min(ordercount)
from voctoberemporders

select * from vempdata


select	voctoberemporders.empid, 
		vempdata.employeename,
		vempdata.managername, 
		vempdata.title, 
		voctoberemporders.Ordercount
from voctoberemporders
left outer join vempdata
on voctoberemporders.empid = vempdata.empid
where ordercount = 
		(select max(ordercount)
		from voctoberemporders)
