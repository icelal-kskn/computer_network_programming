using System;
using System.Management;

class WMICardGrab
{
    public static void Main()
    {
        ManagementObjectSearcher query = new
             ManagementObjectSearcher("SELECT * FROM Win32_NetworkAdapterConfiguration WHERE IPEnabled = 'TRUE'") ;
        ManagementObjectCollection queryCollection = query.Get();
        foreach( ManagementObject mo in queryCollection )
        {
            string[] addresses = (string[])mo["IPAddress"];
            string[] subnets = (string[])mo["IPSubnet"];
            string[] defaultgateways = (string[])mo["DefaultIPGateway"];

            Console.WriteLine("Network Card: {0}", mo["Description"]);
            Console.WriteLine("    MAC Address: {0}", mo["MACAddress"]);

            foreach(string ipaddress in addresses)
            {
                Console.WriteLine("    IP Address: {0}", ipaddress);
            }
            foreach(string subnet in subnets)
            {
                Console.WriteLine("    Subnet Mask: {0}", subnet);
            }
            foreach(string defaultgateway in defaultgateways)
            {
                Console.WriteLine("    Gateway: {0}", defaultgateway);
            }
        }
    }
}