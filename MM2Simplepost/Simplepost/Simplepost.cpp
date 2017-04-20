// Simplepost.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <iostream>//added
#include <Windows.h>
#include <Winhttp.h>
#include <atlstr.h>//For CString

#pragma comment(lib, "winhttp.lib")//Addd to use _WinHttpOpen

//int CheckAOIResult(CStringA &pszInspectionEndTimeFrom, CStringA &pszInspectionEndTimeTo, CStringA &pszSystemMachineName, CStringA &pszBoardId,
//                   CStringA &pszBoardSide, CString &WebServerIPAddress, INTERNET_PORT WebServerPort, CString &WebServerObject, CStringA &pszPostData);
//int CheckAOIResult(CString &WebServerIPAddress, INTERNET_PORT WebServerPort, CString &WebServerObject, CStringA &pszPostData);
//int CheckAOIResult(CString &WebServerIPAddress, INTERNET_PORT WebServerPort, CString &WebServerObject, CString &pszPostData);
int CheckAOIResult(CString &WebServerIPAddress, INTERNET_PORT WebServerPort, CString &WebServerObject, CStringA &pszPostData);
//int CheckAOIResult(CString &WebServerIPAddress, INTERNET_PORT WebServerPort, CString &WebServerObject, CString &pszPostData);

/*
INPUT Data

<?xml version="1.0" encoding= "UTF-8" standalone="yes"?>
<parameterUM>
    <params>
        <param name="inspection_end_time_from" value="20170331130101" />
        <param name="inspection_end_time_to" value="20170331140101" />
        <param name="system_machine_name" value="VPV-MC" />
        <param name="board_id" value = "D7093AGDPYB" />
        <param name="board_side" value = "0" />
        <param name="lang_type" value = "0" />
    </params>
</parameterUM>

*/

/*
OUTPUT Data

<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<resultDataM>
    <output>
        <data>
            <param name="system_machine_name" value="MACHINE 1" />
            <param name="user_machine_name" value="BBB" />
            <param name="project_id" value="CCC Project" />
            <param name="project_revision" value="1.0" />
            <param name="board_name" value="PR Board 00012" />
            <param name="board_width" value="1230898.4" />
            <param name="board_height" value="2376894.5" />
            <param name="program_revision" value="1.0" />
            <param name="program_name" value="Proximity 1" />
            <param name="board_side" value="0" />
            <param name="inspection_process_type" value="1" />
            <param name="machine_type" value="S720" />
            <param name="mask_thickness" value="2345.6" />
            <param name="pg_comment" value="Repaired OK" />
            <param name="inspection_program_update" value="20170101010101" />
            <param name="inspection_id" value="INS7890" />
            <param name="board_id" value="D7093AGDPYB" />
            <param name="lot" value="LOT01" />
            <param name="inspection_end_time" value="20170331130501" />
            <param name="confirm_date" value="20170331131001" />
            <param name="inspection_result_code" value="0" />
            <param name="inspection_result_name" value="OK" />
            <param name="confirm_result_code" value="0" />
            <param name="confirm_result_name" value="OK" />
            <param name="user_confirm_flag" value="1" />
            <param name="inspection_user_id" value="U000234" />
            <param name="inspection_user_name" value="Paul Brown" />
            <param name="confirm_user_id" value="U00012" />
            <param name="confirm_user_name" value="SUSAN P" />
            <param name="line_stop_code" value="0" />
            <param name="ng_point_count" value="0" />
            <param name="component_count" value="1254" />
            <param name="last_result" value="0" />
        </data>

        <data>
            <param name="system_machine_name" value="MACHINE 1" />
            <param name="user_machine_name" value="BBB" />
            <param name="project_id" value="CCC Project" />
            <param name="project_revision" value="1.0" />
            <param name="board_name" value="PR Board 00012" />
            <param name="board_width" value="1230898.4" />
            <param name="board_height" value="2376894.5" />
            <param name="program_revision" value="1.0" />
            <param name="program_name" value="Proximity 1" />
            <param name="board_side" value="0" />
            <param name="inspection_process_type" value="1" />
            <param name="machine_type" value="S720" />
            <param name="mask_thickness" value="2345.6" />
            <param name="pg_comment" value="Repaired OK" />
            <param name="inspection_program_update" value="20170101010101" />
            <param name="inspection_id" value="INS7890" />
            <param name="board_id" value="D7093AGDPYB" />
            <param name="lot" value="LOT01" />
            <param name="inspection_end_time" value="20170331131154" />
            <param name="confirm_date" value="20170331131501" />
            <param name="inspection_result_code" value="0" />
            <param name="inspection_result_name" value="OK" />
            <param name="confirm_result_code" value="0" />
            <param name="confirm_result_name" value="OK" />
            <param name="user_confirm_flag" value="1" />
            <param name="inspection_user_id" value="U000234" />
            <param name="inspection_user_name" value="Paul Brown" />
            <param name="confirm_user_id" value="U00012" />
            <param name="confirm_user_name" value="SUSAN P" />
            <param name="line_stop_code" value="0" />
            <param name="ng_point_count" value="0" />
            <param name="component_count" value="1254" />
            <param name="last_result" value="0" />
        </data>
    </output>
    <recordCount>2</recordCount>
    <returnCode>0</returnCode>
</resultDataM>

*/

char *ReceivedXMLMData =
"< ? xml version = \"1.0\" encoding = \"UTF-8\" standalone = \"yes\" ? >\
<resultDataM>\
<output>\
<data>\
<param name = \"system_machine_name\" value = \"VPV-MC\" / >\
<param name=\"user_machine_name\" value=\"BBB\" />\
<param name = \"project_id\" value = \"CCC Project\" / >\
<param name=\"project_revision\" value=\"1.0\" />\
<param name = \"board_name\" value = \"PR Board 00012\" / >\
<param name=\"board_width\" value=\"1230898.4\" />\
<param name = \"board_height\" value = \"2376894.5\" / >\
<param name=\"program_revision\" value=\"1.0\" />\
<param name = \"program_name\" value = \"Proximity 1\" / >\
<param name=\"board_side\" value=\"0\" />\
<param name = \"inspection_process_type\" value = \"1\" / >\
<param name=\"machine_type\" value=\"S720\" />\
<param name = \"mask_thickness\" value = \"2345.6\" / >\
<param name=\"pg_comment\" value=\"Repaired OK\" />\
<param name = \"inspection_program_update\" value = \"20170101010101\" / >\
<param name=\"inspection_id\" value=\"INS7890\" />\
<param name = \"board_id\" value = \"PCB00012\" / >\
<param name=\"lot\" value=\"LOT01\" />\
<param name = \"inspection_end_time\" value = \"20170331130501\" / >\
<param name=\"confirm_date\" value=\"20170331131001\" />\
<param name = \"inspection_result_code\" value = \"0\" / >\
<param name=\"inspection_result_name\" value=\"OK\" />\
<param name = \"confirm_result_code\" value = \"0\" / >\
<param name=\"confirm_result_name\" value=\"OK\" />\
<param name = \"user_confirm_flag\" value = \"1\" / >\
<param name=\"inspection_user_id\" value=\"U000234\" />\
<param name = \"inspection_user_name\" value = \"Paul Brown\" / >\
<param name=\"confirm_user_id\" value=\"U00012\" />\
<param name = \"confirm_user_name\" value = \"SUSAN P\" / >\
<param name=\"line_stop_code\" value=\"0\" />\
<param name = \"ng_point_count\" value = \"0\" / >\
<param name=\"component_count\" value=\"1254\" />\
<param name = \"last_result\" value = \"0\" / >\
</data>\
<data>\
<param name=\"system_machine_name\" value=\"VPV-MC\" />\
<param name = \"user_machine_name\" value = \"BBB\" / >\
<param name=\"project_id\" value=\"CCC Project\" />\
<param name = \"project_revision\" value = \"1.0\" / >\
<param name=\"board_name\" value=\"PR Board 00012\" />\
<param name = \"board_width\" value = \"1230898.4\" / >\
<param name=\"board_height\" value=\"2376894.5\" />\
<param name = \"program_revision\" value = \"1.0\" / >\
<param name=\"program_name\" value=\"Proximity 1\" />\
<param name = \"board_side\" value = \"0\" / >\
<param name=\"inspection_process_type\" value=\"1\" />\
<param name = \"machine_type\" value = \"S720\" / >\
<param name=\"mask_thickness\" value=\"2345.6\" />\
<param name = \"pg_comment\" value = \"Repaired OK\" / >\
<param name=\"inspection_program_update\" value=\"20170101010101\" />\
<param name = \"inspection_id\" value = \"INS7890\" / >\
<param name=\"board_id\" value=\"PCB00012\" />\
<param name = \"lot\" value = \"LOT01\" / >\
<param name=\"inspection_end_time\" value=\"20170331131154\" />\
<param name = \"confirm_date\" value = \"20170331131501\" / >\
<param name=\"inspection_result_code\" value=\"0\" />\
<param name = \"inspection_result_name\" value = \"OK\" / >\
<param name=\"confirm_result_code\" value=\"0\" />\
<param name = \"confirm_result_name\" value = \"OK\" / >\
<param name=\"user_confirm_flag\" value=\"1\" />\
<param name = \"inspection_user_id\" value = \"U000234\" / >\
<param name=\"inspection_user_name\" value=\"Paul Brown\" />\
<param name = \"confirm_user_id\" value = \"U00012\" / >\
<param name=\"confirm_user_name\" value=\"SUSAN P\" />\
<param name = \"line_stop_code\" value = \"0\" / >\
<param name=\"ng_point_count\" value=\"0\" />\
<param name = \"component_count\" value = \"1254\" / >\
<param name=\"last_result\" value=\"3\" />\
< / data>\
</output>\
< recordCount>2 < / recordCount > \
<returnCode>0</returnCode>\
< / resultDataM>" ;



int CheckResult(char *XMLMData)
{
    //char BoardID[30];
    //char BoardSide;
    //char inspection_end_time[18];
    //char inspection_result_code;
    char LastResult[10];
    int iLastResult = 1;

    char *CurrentXMLMData = XMLMData;
    char *InputStream = NULL;
    char *LastResultValue = NULL;
    char *LastResultValueQuotationMark1 = NULL;
    char *LastResultValueQuotationMark2 = NULL;

    size_t XMLDataLength = strlen(XMLMData);
    size_t CurrentPosition = 0;

    while (CurrentPosition < XMLDataLength && (InputStream = strstr(CurrentXMLMData, "last_result")) != NULL)
    {
        CurrentPosition = CurrentPosition + InputStream - CurrentXMLMData;
        //XMLMData = InputStream + strlen("last_result");
        CurrentXMLMData = InputStream + 1;
    }
    if (strstr(XMLMData + CurrentPosition, "last_result") != NULL)
    {
        LastResultValue = strstr(XMLMData + CurrentPosition, "value");
        if (LastResultValue)
            LastResultValueQuotationMark1 = strstr(LastResultValue + 5, "\"");// to skip space <param name="last_result" value="0" /> => in case <param name="last_result" value = " 0 " />
        if (LastResultValueQuotationMark1)
            LastResultValueQuotationMark2 = strstr(LastResultValueQuotationMark1 + 1, "\"");// to skip space <param name="last_result" value="0" /> => in case <param name="last_result" value = " 0 " />

        if (LastResultValueQuotationMark1 && LastResultValueQuotationMark2)
        {
            memset(LastResult, 0x00, sizeof(LastResult));
            memcpy(LastResult, LastResultValueQuotationMark1 + 1, LastResultValueQuotationMark2 - LastResultValueQuotationMark1 - 1);
            iLastResult = atoi(LastResult);
        }
    }

    return iLastResult;
}


int main(void)
{



    //  http://10.150.104.4:8080/prismRest/resources/GetSystemMachineNameList

    
    ///*
    // OMRON Test server
    CString WebServerIPAddress = "10.150.104.4";
    INTERNET_PORT WebServerPort = 8080;    
    //CString WebServerObject = "/prismRest/resources/GetSystemMachineNameList";
    CString WebServerObject = "/prismRest/resources/GetPcbInfoByBarcode";
    //WebServerObject = "/prismRest/resources/GetUserList";
    //WebServerObject = "/prismRest/resources/GetUserResultName";
    //WebServerObject = "/prismRest/resources/GetProgramList";

    /*
    GetProgramList
    <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
    <parameterUM>
    <params>
    <param name="machine_type_code" value="0"/>
    <param name="insp_process_type_code" value="1"/>
    </params>
    </parameterUM>
    */
    //*/

    /* test
    // http://requestb.in/1kfwodr1 
    // http://requestb.in/1kfwodr1?inspect

    CString WebServerIPAddress = "requestb.in";
    INTERNET_PORT WebServerPort= 80;
    CString WebServerObject = "1kfwodr1";
    */

    ///*
    CStringA pszInspectionEndTimeFrom = "20170331130101";
    CStringA pszInspectionEndTimeTo = "20170406100101";
    CStringA pszSystemMachineName = "VPV-MC";// VPV-MC,VT-S730-0278
    //*/

    /*
    CStringA pszInspectionEndTimeFrom = "";
    CStringA pszInspectionEndTimeTo = "";
    CStringA pszSystemMachineName = "";// VPV-MC,VT-S730-0278
    */


    CStringA pszBoardId = "D7093AGDPYB";

    bool bCanTestBoard = false;
    int iFirstSideResult, iSecondSideResult;
    

    /*
    CStringA pszPostData1 = "<?xml version = \"1.0\" encoding = \"UTF - 8\" standalone = \"yes\"?> <parameterUM> <params> <param name = \"inspection_end_time_from\" value = \"";
    //CStringA pszInspectionEndTimeFrom = "20170331130101";
    CStringA pszPostData2 = "\" /> <param name=\"inspection_end_time_to\" value=\"";
    //CStringA pszInspectionEndTimeTo = "20170331140101";
    CStringA pszPostData3 = "\" /> <param name=\"system_machine_name\" value=\"";
    //CStringA pszSystemMachineName = "VPV-MC";
    CStringA pszPostData4 = "\" /> <param name=\"board_id\" value=\"";
    //CStringA pszBoardId = "D7093AGDPYB";
    CStringA pszPostData5 = "\" /> <param name=\"board_side\" value=\"";
    //CStringA pszBoardSide = "0";
    CStringA pszPostData6 = "\" /> <param name=\"lang_type\" value=\"0\" / > </params> </parameterUM>";
    */

    /*
    CStringA pszPostData1 = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<parameterUM>\n\t<params>\n <param name=\"inspection_end_time_from\" value=\"";
    //CStringA pszInspectionEndTimeFrom = "20170331130101";
    CStringA pszPostData2 = "\" />\n <param name=\"inspection_end_time_to\" value=\"";
    //CStringA pszInspectionEndTimeTo = "20170331140101";
    CStringA pszPostData3 = "\" />\n <param name=\"system_machine_name\" value=\"";
    //CStringA pszSystemMachineName = "VPV-MC";
    CStringA pszPostData4 = "\" />\n <param name=\"board_id\" value=\"";
    //CStringA pszBoardId = "D7093AGDPYB";
    CStringA pszPostData5 = "\" />\n <param name=\"board_side\" value=\"";
    //CStringA pszBoardSide = "0";
    CStringA pszPostData6 = "\" />\n <param name=\"lang_type\" value=\"0\" / >\n\t</params>\n</parameterUM>";
    */

    /*
    CStringA pszPostData1 = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<parameterUM>\n\t<params>\n                         <param name=\"inspection_end_time_from\" value=\"";
    //CStringA pszInspectionEndTimeFrom = "20170331130101";
    CStringA pszPostData2 = "\"/>\n                         <param name=\"inspection_end_time_to\" value=\"";
    //CStringA pszInspectionEndTimeTo = "20170331140101";
    CStringA pszPostData3 = "\"/>\n                         <param name=\"system_machine_name\" value=\"";
    //CStringA pszSystemMachineName = "VPV-MC";
    CStringA pszPostData4 = "\"/>\n                         <param name=\"board_id\" value=\"";
    //CStringA pszBoardId = "D7093AGDPYB";
    CStringA pszPostData5 = "\"/>\n                         <param name=\"board_side\" value=\"";
    //CStringA pszBoardSide = "0";
    CStringA pszPostData6 = "\"/>\n                         <param name=\"lang_type\" value=\"0\"/>\n\t</params>\n</parameterUM>";
    */

    
    CStringA pszPostData1 = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<parameterUM>\n<params>\n    <param name=\"inspection_end_time_from\" value=\"";
    //CStringA pszInspectionEndTimeFrom = "20170331130101";
    CStringA pszPostData2 = "\"/>\n    <param name=\"inspection_end_time_to\" value=\"";
    //CStringA pszInspectionEndTimeTo = "20170331140101";
    CStringA pszPostData3 = "\"/>\n    <param name=\"system_machine_name\" value=\"";
    //CStringA pszSystemMachineName = "VPV-MC";
    CStringA pszPostData4 = "\"/>\n    <param name=\"board_id\" value=\"";
    //CStringA pszBoardId = "D7093AGDPYB";
    CStringA pszPostData5 = "\"/>\n    <param name=\"board_side\" value=\"";
    //CStringA pszBoardSide = "0";
    CStringA pszPostData6 = "\"/>\n    <param name=\"lang_type\" value=\"0\"/>\n</params>\n</parameterUM>";
    

    
    CStringA pszPostData = "";
    //CString pszPostData = "";


    CStringA pszBoardSide = "0";
    pszPostData = pszPostData1 + pszInspectionEndTimeFrom + pszPostData2 + pszInspectionEndTimeTo + pszPostData3 + pszSystemMachineName + pszPostData4 + pszBoardId + pszPostData5 + pszBoardSide + pszPostData6;

    ////////////////////////////////////////////////////////////////////////////////
    //GetUserList test
    //http://10.150.104.4:8080/prismRest/resources/GetUserList?function_id="3"
    //Not work pszPostData1 = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<parameterUM>\n    <params>\n        <param name=\"function_id\" value=\"3\"/>\n    </params>\n</parameterUM>";

/*
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<parameterUM>
<params>
<param name="parameter name" value="parameter value" />
<param name="parameter name" value="parameter value" />
<param name="parameter name" value="parameter value" />
・・・
</params>
</parameterUM>

*/

    //pszPostData1 = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<parameterUM>\n<params>\n<param name=\"function_id\" value=\"3\"/>\n</params>\n</parameterUM>";

    //pszPostData1 = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<parameterUM>\n<params>\n<param name=\"lang_type\" value=\"0\"/>\n</params>\n</parameterUM>";  //Not work
    //pszPostData1 = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<parameterUM>\n<params>\n<param name=\"lang_type\" value=\"0\"/>\n</params>\n</parameterUM>";  //Not work

    //GetUserList
    //pszPostData1 = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<parameterUM>\n<params>\n    <param name=\"function_id\" value=\"3\"/>\n</params>\n</parameterUM>";
    
    //GetProgramList
    //pszPostData1 = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<parameterUM>\n<params>\n    <param name=\"machine_type_code\" value = \"0\"/>\n    <param name=\"insp_process_type_code\" value = \"1\"/>\n</params>\n</parameterUM>";
    
    //GetProgramList
    //pszPostData1 = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<parameterUM>\n<params>\n        <param name=\"insp_process_type_code\" value = \"1\"/>\n</params>\n</parameterUM>";

    //pszPostData = pszPostData1;
    
    
    //GetPcbInfoByBarcode
    //pszPostData = pszPostData;

    ////////////////////////////////////////////////////////////////////////////////
/*

    For WebServerObject = "/prismRest/resources/GetSystemMachineNameList"; test
    pszPostData = "";
    iFirstSideResult = CheckAOIResult( WebServerIPAddress, WebServerPort, WebServerObject, pszPostData);
*/
    iFirstSideResult = CheckAOIResult(WebServerIPAddress, WebServerPort, WebServerObject, pszPostData);

    //pszBoardSide = "1";
    //pszPostData = pszPostData1 + pszInspectionEndTimeFrom + pszPostData2 + pszInspectionEndTimeTo + pszPostData3 + pszSystemMachineName + pszPostData4 + pszBoardId + pszPostData5 + pszBoardSide + pszPostData6;
    //iSecondSideResult = CheckAOIResult(WebServerIPAddress, WebServerPort, WebServerObject, pszPostData);

    if (iFirstSideResult == 0 && iSecondSideResult == 0)
        bCanTestBoard = true;

    getchar();
    //getchar();
    return 0;
}


//int CheckAOIResult(CStringA &pszInspectionEndTimeFrom, CStringA &pszInspectionEndTimeTo, CStringA &pszSystemMachineName, CStringA &pszBoardId,
//                   CStringA &pszBoardSide, CString &WebServerIPAddress, INTERNET_PORT WebServerPort, CString &WebServerObject, CStringA &pszPostData)
//int CheckAOIResult(CString &WebServerIPAddress, INTERNET_PORT WebServerPort, CString &WebServerObject, CString &pszPostData)
int CheckAOIResult(CString &WebServerIPAddress, INTERNET_PORT WebServerPort, CString &WebServerObject, CStringA &pszPostData)
//int CheckAOIResult(CString &WebServerIPAddress, INTERNET_PORT WebServerPort, CString &WebServerObject, CString &pszPostData)
{
    int iTestResult;

    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer;
    BOOL  bResults = FALSE;
    HINTERNET  hSession = NULL,
    hConnect = NULL,
    hRequest = NULL;

    // Use WinHttpOpen to obtain a session handle.
    hSession = WinHttpOpen(L"WinHTTP Example/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);

    /////////////////////////////////////////////////////////////////////////////
    /////  V1
/*
    // Specify an HTTP server.
    if (hSession)
    hConnect = WinHttpConnect(hSession, L"www.microsoft.com",
        INTERNET_DEFAULT_HTTPS_PORT, 0);

    // Create an HTTP request handle.
    if (hConnect)
    hRequest = WinHttpOpenRequest(hConnect, L"GET", NULL,
        NULL, WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE);

    // Send a request.
    if (hRequest)
    bResults = WinHttpSendRequest(hRequest,
        WINHTTP_NO_ADDITIONAL_HEADERS, 0,
        WINHTTP_NO_REQUEST_DATA, 0,
        0, 0);
*/
    /////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////
    /////  V2

    // Specify an HTTP server.
    if (hSession)
        //ms SAMPLE org hConnect = WinHttpConnect(hSession, L"www.wingtiptoys.com",INTERNET_DEFAULT_HTTP_PORT, 0);//ORG
        //hConnect = WinHttpConnect(hSession, L"posttestserver.com", INTERNET_DEFAULT_HTTP_PORT, 0);//works well

        //hConnect = WinHttpConnect(hSession, L"requestb.in", INTERNET_DEFAULT_HTTP_PORT, 0);//works well
        //hConnect = WinHttpConnect(hSession, L"10.150.104.4", 8080, 0);//works well
        //hConnect = WinHttpConnect(hSession, WebServerIPAddress, WebServerPort, 0);//works well
        hConnect = WinHttpConnect(hSession, (LPCWSTR)WebServerIPAddress, WebServerPort, 0);//works well
        //hConnect = WinHttpConnect(hSession, L"posttestserver.com", INTERNET_DEFAULT_HTTP_PORT, 0);//works well


    
    // Create an HTTP Request handle.
    if (hConnect)
        //MS ORG hRequest = WinHttpOpenRequest(hConnect, L"PUT",L"/writetst.txt",  NULL, WINHTTP_NO_REFERER,  WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
        //hRequest = WinHttpOpenRequest(hConnect, L"POST", L"/post.php", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
        //hRequest = WinHttpOpenRequest(hConnect, L"POST", L"/post.php", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_ESCAPE_PERCENT);//works
        //hRequest = WinHttpOpenRequest(hConnect, L"POST", L"rzqoh0rz", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_ESCAPE_PERCENT);//works
        
        //hRequest = WinHttpOpenRequest(hConnect, L"POST", L"rzqoh0rz", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);//test works well
        //hRequest = WinHttpOpenRequest(hConnect, L"POST", L"/prismRest/resources/GetPcbInfoByBarcode", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);//test
        //hRequest = WinHttpOpenRequest(hConnect, L"POST", L"/prismRest/resources/GetSystemMachineNameList", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);//test
        //hRequest = WinHttpOpenRequest(hConnect, L"POST", WebServerObject, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);//test
        //hRequest = WinHttpOpenRequest(hConnect, L"POST", WebServerObject, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);//test
        //hRequest = WinHttpOpenRequest(hConnect, L"POST", WebServerObject, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_ESCAPE_PERCENT);//test
        //hRequest = WinHttpOpenRequest(hConnect, L"GET", (LPCWSTR)WebServerObject, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);//Works well in http://10.150.104.4:8080/prismRest/resources/
        //hRequest = WinHttpOpenRequest(hConnect, L"GET", (LPCWSTR)WebServerObject, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);//Works well in http://10.150.104.4:8080/prismRest/resources/
        //OK hRequest = WinHttpOpenRequest(hConnect, L"GET", (LPCWSTR)WebServerObject, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);//Works well in http://10.150.104.4:8080/prismRest/resources/
        
         //hRequest = WinHttpOpenRequest(hConnect, L"GET", (LPCWSTR)WebServerObject, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);//Works well in http://10.150.104.4:8080/prismRest/resources/
         hRequest = WinHttpOpenRequest(hConnect, L"GET", (LPCWSTR)WebServerObject, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);//Works well in http://10.150.104.4:8080/prismRest/resources/
   
       /*
       //WinHttpSetOption
        DWORD myFeature = WINHTTP_OPTION_DECOMPRESSION;
                                               //WINHTTP_OPTION_ENABLE_FEATURE
        BOOL fRet = WinHttpSetOption(hConnect, WINHTTP_OPTION_DISABLE_FEATURE, &myFeature, sizeof(myFeature));
        */


    //hRequest = WinHttpOpenRequest(hConnect, L"POST", (LPCWSTR)WebServerObject, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);//This codew is not work in http://10.150.104.4:8080/prismRest/resources/GetSystemMachineNameList
        //hRequest = WinHttpOpenRequest(hConnect, L"PUT", (LPCWSTR)WebServerObject, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);//This codew is not work in http://10.150.104.4:8080/prismRest/resources/GetSystemMachineNameList


        //hRequest = WinHttpOpenRequest(hConnect, L"POST", L"/post.php", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);//test

    
    //BOOL result = pFile->SendRequest(strHeaders, (LPVOID)(LPCTSTR)strFormData, strFormData.GetLength());

    // Send a Request.
    //MS org if (hRequest)
        //MS org bResults = WinHttpSendRequest(hRequest,WINHTTP_NO_ADDITIONAL_HEADERS,0, WINHTTP_NO_REQUEST_DATA, 0,0, 0);
       

    //////////////////////////////////////////////////////////////////////////////////
    // Apr. 5, 2017 test
    // Write data to the server.
    //LPSTR pszData = "WinHttpWriteData Example";

   /* LPSTR pszData = "< ? xml version = \"1.0\" encoding = \"UTF - 8\" standalone = \"yes\" ? >" */
    /*
        //CString
    LPSTR pszData = "< ? xml version = \"1.0\" encoding = \"UTF - 8\" standalone = \"yes\" ? >\
        <parameterUM>\
        <params>\
        <param name = \"inspection_end_time_from\" value = \"20170331130101\" / >\
        <param name = \"inspection_end_time_to\" value = \"20170331140101\" / >\
        <param name = \"system_machine_name\" value = \"MACHINE 1\" / >\
        <param name = \"board_id\" value = \"PCB00012\" / >\
        <param name = \"board_side\" value = \"0\" / >\
        <param name = \"lang_type\" value = \"0\" / >\
        < / parameterUM>";
*/


/*
  CStringA pszData = "< ? xml version = \"1.0\" encoding = \"UTF - 8\" standalone = \"yes\" ? >\
 <parameterUM>\
 <params>\
 <param name = \"inspection_end_time_from\" value = \"20170331130101\" / >\
 <param name = \"inspection_end_time_to\" value = \"20170331140101\" / >\
 <param name = \"system_machine_name\" value = \"MACHINE 1\" / >\
 <param name = \"board_id\" value = \"PCB00012\" / >\
 <param name = \"board_side\" value = \"0\" / >\
 <param name = \"lang_type\" value = \"0\" / >\
 < / parameterUM>";
 */
    /*
    CStringA pszPostData1 = "< ? xml version = \"1.0\" encoding = \"UTF - 8\" standalone = \"yes\" ? > <parameterUM> <params> <param name = \"inspection_end_time_from\" value = \"";
    //CStringA pszInspectionEndTimeFrom = "20170331130101";
    CStringA pszPostData2 = "\" / > <param name = \"inspection_end_time_to\" value = \"";
    //CStringA pszInspectionEndTimeTo = "20170331140101";
    CStringA pszPostData3 = "\" / > <param name = \"system_machine_name\" value = \"";
    //CStringA pszSystemMachineName = "MACHINE 1";
    CStringA pszPostData4 = "\" / > <param name = \"board_id\" value = \"";
    //CStringA pszBoardId = "D7093AGDPYB";
    CStringA pszPostData5 = "\" / > <param name = \"board_side\" value = \"";
    //CStringA pszBoardSide = ""0";
   CStringA pszPostData6 = "\" / > <param name = \"lang_type\" value = \"0\" / > < / parameterUM>";

    CStringA pszData = pszPostData1 + pszInspectionEndTimeFrom + pszPostData2 + pszInspectionEndTimeTo + pszPostData3 + pszSystemMachineName + pszPostData4 + pszBoardId + pszPostData5 + pszBoardSide + pszPostData6;
    */

    //bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, &pszData, (DWORD)strlen(pszData), 0, 0);
    if (hRequest)
    {
        //bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, &pszData, (DWORD)pszData.GetLength(), (DWORD)pszData.GetLength(), 0);
        //bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, &pszData, (DWORD)strlen(pszData), (DWORD)strlen(pszData), 0);//works
        //bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, pszData, (DWORD)strlen(pszData), (DWORD)strlen(pszData), 0);//also works

       //bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, pszData.GetBuffer(), (DWORD)pszData.GetLength(), (DWORD)pszData.GetLength(), 0);//also works

       //bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);//Works for "/prismRest/resources/GetSystemMachineNameList";
       //bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, pszPostData.GetBuffer(), (DWORD)pszPostData.GetLength(), (DWORD)pszPostData.GetLength(), 0);//also works
       //bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, (LPVOID)pszPostData.GetBuffer(), (DWORD)pszPostData.GetLength(), (DWORD)pszPostData.GetLength(), 0);//also works
       //bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, (LPVOID)(LPCSTR) pszPostData, (DWORD)pszPostData.GetLength(), (DWORD)pszPostData.GetLength(), 0);//also works
        //bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, (LPVOID)(LPCWSTR)pszPostData, (DWORD)pszPostData.GetLength() * 2, (DWORD)pszPostData.GetLength() * 2, 0);//also works
        //test
        int ii = (DWORD)pszPostData.GetLength();
        //bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, (DWORD)pszPostData.GetLength(), 0);
        //bResults = WinHttpSendRequest(hRequest, L"content-type:application/x-www-form-urlencoded", 0, WINHTTP_NO_REQUEST_DATA, 0, (DWORD)pszPostData.GetLength(), 0);
        //bResults = WinHttpSendRequest(hRequest, L"content-type:application/xml;Charset=ISO-8859-1", 0, (LPVOID)(LPCWSTR)pszPostData, (DWORD)pszPostData.GetLength() * 2, (DWORD)pszPostData.GetLength() * 2, 0);//also works      
        //bResults = WinHttpSendRequest(hRequest, L"content-type:application/xml;Charset=ISO-8859-1", 0, (LPVOID)(LPCSTR)pszPostData, (DWORD)pszPostData.GetLength(), (DWORD)pszPostData.GetLength(), 0);//Not works      
        //bResults = WinHttpSendRequest(hRequest, L"content-type:application/xml;Charset=UTF-8", 0, (LPVOID)(LPCWSTR)pszPostData, (DWORD)pszPostData.GetLength() * 2, (DWORD)pszPostData.GetLength() * 2, 0);//Not works      
        //bResults = WinHttpSendRequest(hRequest, L"content-type:application/xml;Charset=ISO-8859-1", 0, (LPVOID)(LPCWSTR)pszPostData, (DWORD)pszPostData.GetLength() * 2, (DWORD)pszPostData.GetLength() * 2, 0);//also works      
        //bResults = WinHttpSendRequest(hRequest, L"content-type:application/xml;Charset=ISO-8859-1", 0, (LPVOID)(LPCWSTR)pszPostData, (DWORD)pszPostData.GetLength(), (DWORD)pszPostData.GetLength(), 0);//also works      
        //bResults = WinHttpSendRequest(hRequest, L"content-type:application/xml;Charset=UTF-8", 0, (LPVOID)(LPCWSTR)pszPostData, (DWORD)pszPostData.GetLength() * 2, (DWORD)pszPostData.GetLength() * 2, 0);//Not works      
        //bResults = WinHttpSendRequest(hRequest, L"content-type:application/xml;Charset=UTF-8", 0, (LPVOID)(LPCSTR)pszPostData, (DWORD)pszPostData.GetLength(), (DWORD)pszPostData.GetLength(), 0);//Not works      
        
        
        //Requext XML output 
        //printf("%s", (LPCSTR)pszPostData);//Apr. 10, 2017 added for Query string


        bResults = WinHttpSendRequest(hRequest, L"content-type:application/xml;Charset=UTF-8", 0, WINHTTP_NO_REQUEST_DATA, 0, (DWORD)pszPostData.GetLength(), 0);



        //.bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, (LPVOID)(LPCSTR)pszPostData, (DWORD)pszPostData.GetLength(), (DWORD)pszPostData.GetLength(), 0);//Not works      
        //bResults = WinHttpSendRequest(hRequest, L"content-type:application/x-www-form-urlencoded", -1, (LPVOID)(LPCSTR)pszPostData, (DWORD)pszPostData.GetLength(), (DWORD)pszPostData.GetLength(), 0);//Not works      

    }
    // Write data to the server.
    DWORD dwBytesWritten = 0; 
    if (bResults)
    {

        bResults = WinHttpWriteData(hRequest, (LPVOID)(LPCSTR)pszPostData, (DWORD)pszPostData.GetLength(), &dwBytesWritten);
    }
        //bResults = WinHttpWriteData(hRequest, (LPVOID)pszPostData.GetBuffer(), (DWORD)pszPostData.GetLength(), &dwBytesWritten);
    /////////////////////////////////////////////////////////////////////////////////

   
    //ex 
    /*
    // Create an HTTP Request handle.
    if (hConnect)
        hRequest = WinHttpOpenRequest(hConnect, L"PUT",
            L"/writetst.txt",
            NULL, WINHTTP_NO_REFERER,
            WINHTTP_DEFAULT_ACCEPT_TYPES,
            0);

    // Send a Request.
    if (hRequest)
        bResults = WinHttpSendRequest(hRequest,
            WINHTTP_NO_ADDITIONAL_HEADERS,
            0, WINHTTP_NO_REQUEST_DATA, 0,
            (DWORD)strlen(pszData), 0);

    // Write data to the server.
    if (bResults)
        bResults = WinHttpWriteData(hRequest, pszData,
        (DWORD)strlen(pszData),
            &dwBytesWritten);
    */
    //eND ex
        /////////////////////////////////////////////////////////////////////////////

        // End the request.
    if (bResults)
    bResults = WinHttpReceiveResponse(hRequest, NULL);

    // Keep checking for data until there is nothing left.
    if (bResults)
    {
        do
        {
            // Check for available data.
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
                printf("Error %u in WinHttpQueryDataAvailable.\n",
                    GetLastError());

            // Allocate space for the buffer.
            pszOutBuffer = new char[dwSize + 1];
            if (!pszOutBuffer)
            {
                printf("Out of memory\n");
                dwSize = 0;
            }
            else
            {
                // Read the data.
                ZeroMemory(pszOutBuffer, dwSize + 1);

                if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
                    dwSize, &dwDownloaded))
                    printf("Error %u in WinHttpReadData.\n", GetLastError());
                else
                    printf("%s", pszOutBuffer);

                iTestResult =  CheckResult(ReceivedXMLMData);// need to change to pszOutBuffer

                // Free the memory allocated to the buffer.
                delete[] pszOutBuffer;
            }
        } while (dwSize > 0);
    }


    // Report any errors.
    if (!bResults)
    printf("Error %d has occurred.\n", GetLastError());

    // Close any open handles.
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);

    return iTestResult;
}

/*


BOOL  bResults = FALSE;
HINTERNET hSession = NULL,
hConnect = NULL,
hRequest = NULL;

// Use WinHttpOpen to obtain a session handle.
hSession = WinHttpOpen(  L"A WinHTTP Example Program/1.0",
WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
WINHTTP_NO_PROXY_NAME,
WINHTTP_NO_PROXY_BYPASS, 0);

// Specify an HTTP server.
if (hSession)
hConnect = WinHttpConnect( hSession, L"www.wingtiptoys.com",
INTERNET_DEFAULT_HTTP_PORT, 0);

// Create an HTTP Request handle.
if (hConnect)
hRequest = WinHttpOpenRequest( hConnect, L"PUT",
L"/writetst.txt",
NULL, WINHTTP_NO_REFERER,
WINHTTP_DEFAULT_ACCEPT_TYPES,
0);

// Send a Request.
if (hRequest)
bResults = WinHttpSendRequest( hRequest,
WINHTTP_NO_ADDITIONAL_HEADERS,
0, WINHTTP_NO_REQUEST_DATA, 0,
0, 0);

// PLACE ADDITIONAL CODE HERE.

// Report any errors.
if (!bResults)
printf( "Error %d has occurred.\n", GetLastError());

// Close any open handles.
if (hRequest) WinHttpCloseHandle(hRequest);
if (hConnect) WinHttpCloseHandle(hConnect);
if (hSession) WinHttpCloseHandle(hSession);
*/


/*
#include <afxinet.h>

void DisplayPage(LPCTSTR pszURL)
{
    CInternetSession session(_T("My Session"));
    CStdioFile* pFile = NULL;
    CHAR szBuff[1024];
    //use a URL and print a Web page to the console
    pFile = session.OpenURL(pszURL);
    while (pFile->Read(szBuff, 1024) > 0)
    {
        printf_s("%1023s", szBuff);
    }
    delete pFile;
    session.Close();
}
*/



/*
//Download a Web Page

//using     CInternetSession,CHttpConnection,CHttpFile

//this code excerpt also demonstrates try/catch exception handling
#include <afxinet.h>

void DisplayHttpPage(LPCTSTR pszServerName, LPCTSTR pszFileName)
{
    CInternetSession session(_T("My Session"));
    CHttpConnection* pServer = NULL;
    CHttpFile* pFile = NULL;
    try
    {
        CString strServerName;
        INTERNET_PORT nPort = 80;
        DWORD dwRet = 0;

        pServer = session.GetHttpConnection(pszServerName, nPort);
        //pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, pszFileName);//HTTP_VERB_POST
        //pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST, pszFileName);//HTTP_VERB_POST : Apr.4, 2017 test


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Post test

        DWORD HttpRequestFlags;
        HttpRequestFlags = INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE;

        //CString Process = "rzqoh0rz";

        //test 1 CString Process = _T("/cgi-bin/camera.cgi");
        //Test 2 
        CString Process = "post.php"; http://posttestserver.com/post.php  //works well

        //Test 3 CString Process = "GetPcbInfoByBarcode"; ////for test OEDC-AOI
        


        //CString strFormData = _T("name=John+Doe&userid=hithere&other=P%26Q");
        CString strFormData = "< ? xml version = \"1.0\" encoding = \"UTF - 8\" standalone = \"yes\" ? >\
            "<parameterUM>\
            "<params>\
            "<param name = \"inspection_end_time_from\" value = \"20170331130101\" / >\
            "<param name = \"inspection_end_time_to\" value = \"20170331140101\" / >\
            "<param name = \"system_machine_name\" value = \"MACHINE 1\" / >\
            "<param name = \"board_id\" value = \"PCB00012\" / >\
            "<param name = \"board_side\" value = \"0\" / >\
            "<param name = \"lang_type\" value = \"0\" / >\
            "< / parameterUM>";

        int iDataLength = strFormData.GetLength();
        //CString strFormData = _T("aaaaaabbbbbbbccccccddddddeeeeeefffffggggghhhhhhhhhhhhhhhhhhhhhhHHHHHHHHHHHHH");


        //pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST,Process, NULL, 1, NULL, (LPCTSTR)"1.0", HttpRequestFlags);
        pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST, Process, NULL, 1, NULL, (LPCTSTR)"1.1", HttpRequestFlags);

        //pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST, Process, (LPCTSTR)"AABBCCDD", 9, NULL, (LPCTSTR)"1.0", HttpRequestFlags);
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        //pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, _T("/GetPcbInfoByBarcode.htm"));//HTTP_VERB_POST
        //pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, _T(""));//HTTP_VERB_POST


        //CString strServerName = L"http://localhost";
        //pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, L"/com.test.simpleServlet/api/customers");




        //ORG pFile->SendRequest();

        /////////////////////////////////////////////////////////////////////////////////////////////////////
        //CString strHeaders = _T("Content-Type: application/x-www-form-urlencoded");
        
        CString strHeaders = "Accept: text/*\r\n";
        strHeaders += "User-Agent: HttpCall\r\n";
        strHeaders += "Accept-Language: en-us\r\n";

        BOOL result = pFile->SendRequest(strHeaders, (LPVOID)(LPCTSTR)strFormData, strFormData.GetLength());
        /////////////////////////////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////////
        ////////DWORD dwInfoLevel = HTTP_QUERY_CONTENT_LENGTH;
        ////////LPVOID lpvBuffer;
        ////////char ContentsLength[30];
        ////////LPDWORD lpdwBufferLength = 30;
        ////////DWORD lpdwBufferLength = 30;

        ////////pFile->QueryInfo(dwInfoLevel, ContentsLength, (LPDWORD)&lpdwBufferLength);
        ////////pFile->QueryInfo(dwInfoLevel, (LPVOID)ContentsLength, (LPDWORD)&lpdwBufferLength);


        long MaxLDataReceived = pFile->GetLength();
        ///////////////////////////////////////////////////////////////////////////////////


        pFile->QueryInfoStatusCode(dwRet);

        if (dwRet == HTTP_STATUS_OK)
        {
            CHAR szBuff[1024];
            UINT ReceivedDataLength;
            memset(szBuff, 0x00, 1024);
            while ((ReceivedDataLength = pFile->Read(szBuff,1024)) > 0)
            {
                //printf_s("%1023s", szBuff);

                //printf_s("%1023s", szBuff);
                printf_s("%s", szBuff);
                //memset(szBuff, 0x00, 1024);

            }
        }
        delete pFile;
        delete pServer;
    }
    catch (CInternetException* pEx)
    {
        //catch errors from WinInet
        TCHAR pszError[64];
        pEx->GetErrorMessage(pszError, 64);
        _tprintf_s(_T("%63s"), pszError);
    }
    session.Close();
}
*/

