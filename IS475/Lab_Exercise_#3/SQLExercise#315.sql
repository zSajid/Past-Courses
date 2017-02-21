select ename,
	commission
from emp2
where commission = 
	(select max(commission) 
		from emp2)