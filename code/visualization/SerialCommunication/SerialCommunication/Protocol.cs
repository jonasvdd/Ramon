using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SerialCommunication
{
    public enum DataTypes { q, p, t };

    public static class Protocol
    {
        public static char startChar = 's';
        public static char endchar = 'e';
    }
}
