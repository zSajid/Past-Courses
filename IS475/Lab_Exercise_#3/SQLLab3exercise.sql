select * 
from emp1;

select ename, salary, hiredate, deptno
from emp1;

select ename as 'employee name', 
	salary as 'Current Salary',
	hiredate as 'Date Hired', 
		deptno as 'department Number'
		from emp1; 

select ename 'employee name', 
		salary 'Current Salary', 
		hiredate 'Date Hired', 
		deptno 'department Number'
from emp1
order by deptno;

select lower(ename) 'employee name', 
	salary 'Current Salary', 
	hiredate 'Date Hired', 
	deptno 'department Number'
from emp1
order by deptno;

select ename 'Employee Name', 
	Salary, 
	Commission, 
	Salary + Commission 'Total Remuneration'
	from emp1
	order by ename;

select ename 'Employee Name', 
	Salary, 
	Commission, 
	Salary + ISNULL(Commission, 0) 'Total Remuneration'
	from emp1
	order by ename;
	
select ename 'Employee Name', 
	Salary, 
	Commission, 
	Salary + ISNULL(Commission, 0) 'Current Remuneration',
	(Salary +ISNULL(Commission, 0)) * 1.20 'New Remuneration'
	from emp1
	order by ename;

select ename 'Employee Name', 
	Salary, 
	Commission, 
	Salary + ISNULL(Commission, 0) 'Current Remuneration',
	cast(((Salary +ISNULL(Commission, 0)) * 1.20) as money) 'New Remuneration'
	from emp1
	order by ename;

select ename 'Employee Name', 
	salary 'Current Salary', 
	hiredate 'Date Hired', 
	deptno	'Department Number'
from emp1
where deptno = 20
order by ename;

select ename 'Employee Name', 
	salary 'Current Salary', 
	hiredate 'Date Hired', 
	deptno	'Department Number'
from emp1
where deptno = 20 or deptno = 30
order by ename;

select ename 'Employee Name', 
	salary 'Current Salary', 
	hiredate 'Date Hired', 
	deptno	'Department Number'
from emp1
order by deptno;


select ename 'Employee Name', 
	salary 'Current Salary', 
	cast(hiredate as varchar) 'Date Hired', 
	deptno	'Department Number'
from emp1
order by deptno;


select ename 'Employee Name', 
	Salary 
	Deptno 'Department Number', 
	convert(varchar, HireDate, 107)'Date Hired'
from emp1
order by ename;

select ename 'Employee Name', 
	Salary, 
	Deptno 'Department Number', 
	convert(varchar, Hiredate, 101) 'Date Hired'
from emp1
order by ename;


select empno 'Employee Number', 
	ename 'Employee Name', 
	hiredate 'Date Hired', 
	DATEDIFF(day, hiredate, getdate())
				'Number of days employed', 
	DATEDIFF(month, hiredate, getdate())
				'Number of months employed', 




