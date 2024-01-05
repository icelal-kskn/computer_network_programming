using System;

[Serializable]
public class SerialEmployee
{
   public int EmployeeID;
   public string LastName;
   public string FirstName;
   public int YearsService;
   public double Salary;

   public SerialEmployee()
   {
      EmployeeID = 0;
      LastName = null;
      FirstName = null;
      YearsService = 0;
      Salary = 0.0;
   }
}