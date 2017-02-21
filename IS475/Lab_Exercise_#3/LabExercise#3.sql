select empno, 
		ename, 
		hiredate, 
		citywork, 
		jobtitle, 
		salary, 
		isnull(commission, 0) commission
		salary + isnull(commission, 0) TotalPay
from emp2
where (CityWork like 'San%') and
(salary + isnull(commission,0) > 5000) and salary + isnull(commission,0) < 12000;
