/**************************************************************************************************
** FileName     :  version.cpp
** Author       :  Charlie Wong, ChangSha/HunNan/China
** EMail        :  1213charlie@163.com
** HomePage     :  https://github.com/charlie-wong/
** Date/Time    :  16/01/04 21:38:47
** Description  :  
** License      :  GNU General Public License v3 for 'version'
**                 See <http://www.gnu.org/licenses/> for more details.
**************************************************************************************************/
#include <iostream>
#include "setting.h"
#include "help.h"
int LanguagePriorityList[2] = {2, 1};
int SearchLanguage = 0;
int SearchAreaNum  = 0;
int SearchAreaList[10];
bool MutilMatchShowFileList = true;

int main(int argc, char **argv)
{
    writeVersionInfoToFile("./","version");
    return 0;
}
