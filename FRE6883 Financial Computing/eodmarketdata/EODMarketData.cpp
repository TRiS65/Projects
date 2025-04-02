#include <cstring>
#include <string> 
#include <iostream>
#include <sstream>  
#include <vector>
#include <locale>
#include <iomanip>
#include <fstream>
#include "curl/curl.h"

// #include <limits>
#include <cmath>

using namespace std;
const char* cIWB3000SymbolFile = "Russell_3000_component_stocks.csv";

void populateSymbolVector(vector<string>& symbols)
{
	ifstream fin;
	fin.open(cIWB3000SymbolFile, ios::in);
	string line, name, symbol;
	while (!fin.eof())
	{
		getline(fin, line);
		stringstream sin(line);
		getline(sin, symbol, ',');
		getline(sin, name);
		symbols.push_back(symbol);
	}
}

int write_data(void* ptr, int size, int nmemb, FILE* stream)
{
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}

struct MemoryStruct {
	char* memory;
	size_t size;
};

void* myrealloc(void* ptr, size_t size)
{
	if (ptr)
		return realloc(ptr, size);
	else
		return malloc(size);
}

int write_data2(void* ptr, size_t size, size_t nmemb, void* data)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct* mem = (struct MemoryStruct*)data;
	mem->memory = (char*)myrealloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return realsize;
}

int main(void)
{
	vector<string> symbolList;
	populateSymbolVector(symbolList);

	// file pointer to associate with the file Results.txt for storing the data
	FILE* fp;

	const char resultfilename[FILENAME_MAX] = "Results.txt";

	// declare a pointer of CURL
	CURL* handle;

	CURLcode status;

	// set up the program environment that libcurl needs
	curl_global_init(CURL_GLOBAL_ALL);

	// curl_easy_init() returns a CURL easy handle
	handle = curl_easy_init();

	// if everything's all right with the easy handle
	if (handle)
	{
		string url_common = "https://eodhistoricaldata.com/api/eod/";
		string start_date = "2024-01-01";
		string end_date = "2024-11-30";
		string api_token = "674e89c9855262.94531036";  // You must replace this API token with yours
			
		vector<string>::iterator itr = symbolList.begin();
		for (; itr != symbolList.end(); itr++)
		{	
			struct MemoryStruct data;
			data.memory = NULL;
			data.size = 0;

			string symbol = *itr;
			if(symbol != "ABNB") continue;	// Ruisi Chen: ABNB

			string url_request = url_common + symbol + ".US?" + "from=" + start_date + "&to=" + end_date + "&api_token=" + api_token + "&period=d";
			curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());

			//adding a user agent
			curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
			fp = fopen(resultfilename, "ab");
			fprintf(fp, "%s\n", symbol.c_str());
			
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
			
			// retrieve data
			status = curl_easy_perform(handle);
			
			fprintf(fp, "%c", '\n');
			fclose(fp);
			// check for errors
			if (status != CURLE_OK) {
				cout << "curl_easy_perform() failed: " << curl_easy_strerror(status) << endl;
				return -1;
			}

			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);

			// retrieve data
			status = curl_easy_perform(handle);

			if (status != CURLE_OK)
			{
				cout << "curl_easy_perform() failed: " << curl_easy_strerror(status) << endl;
				return -1;
			}
			
			stringstream sData;
			sData.str(data.memory);
			string sValue, sDate;
			double dValue = 0;
			// double dOpen = 0, dClose = 0;
			// string sMinOpenDate, sMaxCloseDate;
			// double dMinOpenPrice=numeric_limits<double>::max(), dMaxClosePrice=numeric_limits<double>::min();
			vector<double> Adj_Close;
			vector<string> Store_Dates;
			string line;
			cout << "Symbol: " << symbol << endl << endl;
			while (getline(sData, line)) {
				size_t found = line.find('-');
				if (found != std::string::npos)
				{	// Date, Open, High, Low, Close, Adj_Close, Vol.
					// cout << line << endl;

					sDate = line.substr(0, line.find_first_of(','));
					// date_format = yyyy-mm-dd
					if(sDate >= "2024-11-22" and sDate <= "2024-11-27") {
						cout << line << endl;
						Store_Dates.push_back(sDate);
						line.erase(line.find_last_of(','));		// remove Vol.
						dValue = strtod(line.substr(line.find_last_of(',') + 1).c_str(), NULL);
						Adj_Close.push_back(dValue);

						// sValue = line.substr(line.find_first_of(',')+1);		// remove Date
						// dOpen = strtod(sValue.substr(0, sValue.find_first_of(',')).c_str(), NULL);
						// line.erase(line.find_last_of(','));						// remove Vol.
						// line.erase(line.find_last_of(',')); 					// remove Adj_Close
						// dClose = strtod(line.substr(line.find_last_of(',') + 1).c_str(), NULL);
						// if (dOpen < dMinOpenPrice){
						// 	dMinOpenPrice = dOpen; sMinOpenDate = sDate;
						// }
						// if (dClose > dMaxClosePrice){
						// 	dMaxClosePrice = dClose; sMaxCloseDate = sDate;
						// }
					}
					// line.erase(line.find_last_of(','));
					// sValue = line.substr(line.find_last_of(',') + 1);
					// dValue = strtod(sValue.c_str(), NULL);
					// cout << sDate << " " << std::fixed << ::setprecision(2) << dValue << endl;

				}
			}
			// cout << "sMinOpenDate=" << sMinOpenDate << ", dMinOpenPrice=" 
			//      << std::fixed << ::setprecision(2) << dMinOpenPrice << endl;
			// cout << "sMaxCloseDate=" << sMaxCloseDate << ", dMaxClosePrice=" 
			//      << std::fixed << ::setprecision(2) << dMaxClosePrice << endl;

			cout << endl;
			cout << left 
				 << setw(12) << "Date"
				 << setw(10) << "PrevClose"
				 << setw(10) << "Close"
				 << setw(10) << "DailyRtn"
				 << endl;
			int n = Adj_Close.size();
			for (int i = 0; i < (n-1); i++){
				cout << fixed << setprecision(2)
					 << setw(12) << Store_Dates[i+1] 
					 << setw(10) << Adj_Close[i] 
					 << setw(10) << Adj_Close[i+1] 
					 << setw(10) << log(Adj_Close[i+1]/Adj_Close[i]) * 100
					 << endl;
			}
			

			free(data.memory);
			data.size = 0;
		}

	}
	else
	{
		cout << "Curl init failed!" << endl;
		return -1;
	}

	// cleanup what is created by curl_easy_init
	curl_easy_cleanup(handle);

	// release resources acquired by curl_global_init()
	curl_global_cleanup();

	return 0;
}

/*

Symbol: ABNB

2024-11-22,133.3,140.76,133.3,137.34,137.34,6301100
2024-11-25,138.01,141,137.75,140.93,140.93,7930535
2024-11-26,140.78,141.75,139.18,139.67,139.67,3228419
2024-11-27,139.67,140.41,137.68,138.28,138.28,2657033

Date        PrevClose Close     DailyRtn  
2024-11-25  137.34    140.93    2.58      
2024-11-26  140.93    139.67    -0.90     
2024-11-27  139.67    138.28    -1.00 

*/
