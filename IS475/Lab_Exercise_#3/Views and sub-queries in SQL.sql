drop view vEmpData
create view vEmpData as
select	emp.empid, 
		emp.empname EmployeeName,
		emp.payrate, 
		emp.jobtitleid, 
		title, 
		mgr.empname ManagerName
from emp
left outer join jobtitle jt
on emp.jobtitleid = jt.jobtitleid
left outer join emp mgr
on emp.empmgrid = mgr.empid