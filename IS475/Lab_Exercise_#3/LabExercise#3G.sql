SELECT empno,
 Ename,
 Hiredate,
 Citywork,
 Jobtitle,
 Salary,
 ISNULL(convert(varchar, commission), 'No Commission') Commission,
 Salary + ISNULL(commission,0) TotalPay,
 CASE
WHEN salary + ISNULL(commission,0) >= 10000
 THEN 'Very High Pay'
WHEN salary + ISNULL(commission,0) >= 9000
 THEN 'High Pay'
WHEN salary + ISNULL(commission,0) >= 5400
 THEN 'Regular Pay'
ELSE
 NULL
 END PayMessage
FROM emp2
WHERE CityWork like 'San%' and
Salary + ISNULL(commission,0) > 5000 and salary + ISNULL(commission,0) < 12000