select AVG(salary)
from emp2

select round(avg(salary), 2) averageSalary
from emp2
where jobtitle = 'salesman';

select count(*) CountOfRows
from emp2
where jobtitle = 'salesman';

select sum(salary) TotalSalary, 
		sum(salary + isnull(commission, 0)) TotalBucks, 
		avg(salary) AverageSalary, 
		Min(salary) SmallestSalary, 
		Max(salary) BiggestSalary,
		count(*) TotalEmployees
from emp2

/*
Cannot combine aggregate functions with non aggregate functions
No aggregate function in a where clause, has to be in the having function
*/
select  
		sum(salary) TotalSalary, 
		sum(salary + isnull(commission, 0)) TotalBucks, 
		avg(salary) AverageSalary, 
		Min(salary) SmallestSalary, 
		Max(salary) BiggestSalary,
		count(*) TotalEmployees
from emp2
group by deptno
having avg(salary) > 4000