#include "TrieArticles.hpp"

template<typename Out>
void split(const string &s, char delim, Out result){
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> split(const string &s, char delim){
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

bool excludeArticles(string CheckString){
	bool isArticle;
	
	if(CheckString!= " " &&  CheckString!= "a" && CheckString!= "an" && CheckString!= "the" && CheckString!= "but" &&	CheckString!= "and" && CheckString!= "or" &&
	CheckString!="A" && CheckString!= "An" && CheckString!="AN" && CheckString!="And" && CheckString!= "AND" && CheckString!= "The" && CheckString!="THE" &&
	CheckString!="OR" && CheckString!="Or" && CheckString!="BUT" && CheckString!="But"){
		return true;
	}
	else{
		return false;
	}
}

trie::trie(){
    root.endOfWord = false;
}

void trie::insert(string word, int CountCompanyOccurrenceIndex){
    trieNode* current = &root;
    
    for(int i=0; i<word.length(); i++){
        char ch = word[i];
                            
        if(((int) ch == 32) || ( (int) ch >= 65 && (int) ch <= 90 ) || ((int) ch >= 97 && (int) ch <= 122)){
            map<char, trieNode> ::iterator it;
            it = current->children.find(ch);
        
            // if char does not exist in current node, 
            // insert it into current node's map and point to a new empty leaf node with EOW = false
            if(it == current->children.end()){
                trieNode nextNode;
                nextNode.endOfWord = false;
                current->children.insert(pair<char, trieNode>(ch, nextNode));
            }
            
            // if char exists in current node, navigate to the next node it points to
            it = current->children.find(ch);
            current = &(it->second);
        }
    }
    
    // final character of word should have endOfWord = true
    (*current).endOfWord = true;
		
    // initialize countCompanyOccurence for newly company to 0
	CountCompanyOccurrence[CountCompanyOccurrenceIndex] = 0;
	(*current).pointerToGlobalCountCompanyOccurrenceArray = &CountCompanyOccurrence[CountCompanyOccurrenceIndex];
}

bool trie::search(string word){			
    trieNode* current = &root;
    map<char, trieNode> ::iterator it;
    char ch;
    
    for(int i=0; i<word.length(); i++){
        ch = word[i];
		
		if(((int)ch == 32) || ((int)ch >= 65 && (int)ch <= 90) || ((int)ch >= 97 && (int)ch <= 122)){
			it = current->children.find(ch);
        
			// if char does not exist in current node's children map, return false
			if(it == current->children.end()){
				return false;
			}
			current = &(it->second);
		}
    }
    
    // if search is successful (all chars parsed), it must end in a node with EOW = true
	if(current->endOfWord == true){
        *(*current).pointerToGlobalCountCompanyOccurrenceArray = *(*current).pointerToGlobalCountCompanyOccurrenceArray + 1;
	}
	
    return current->endOfWord;
}

// argc is a CLI parameter, corresponds to article.txt file name
int main( int argc, char** argv )
{
    ifstream iFile;
 	string companyFilePath, articleFilePath;
	string companyNames;
	char inputchar;
	string createCompanyName;
	string createCompanyName2words;
	string createCompanyName3words;
    string createCompanyName4words;
	int TotalWordCount = 0;
	char specialChar;
	float relevance = 0;
	int TotalHitCount = 0;
	float TotalRelevance = 0;
	string PeriodLine;
	bool isLinePeriod;
	string CompanyNamewithApos ;
	string CompanyNamewithoutApos;
	
	vector<string> vecCompanyNames;
	vector<string> vecPrimaryCompanyNames;
	vector<string> vecSearchCompanyNames;
	vector<string> vecBreakCompanyNames;
	
	string delimiter = "\t";
	string aposdelimit = "'";
	bool searchResult;
	bool searchResultApos;
	
	//initialize an instance of Trie class
	trie trieInstance;
    
    cout<<"\n\n>>>>>>>>>>>-    WELCOME TO TRIE-BASED ARTICLE ANALYZER    -<<<<<<<<<<";
    cout<<"\n\nUser inputs required:\n1.  File path+name for company(.dat or .txt): This file contains company primary names + aliases ";
    cout<<"\n2.  File path+name for article(.dat or .txt): This file contains article to be analyzed ";
    cout<< "\n\nEnter company file path+name (example- C:\\Users\\User1\\Desktop\\company.dat):  " ;
	cin>>companyFilePath;
        
    // opeen file company.dat and read it    
    iFile.open(companyFilePath.c_str()); 
    while(!iFile.is_open()){
        cout<<"\n\nFile open failed. Try again!";
        cout<<"\n\nEnter full company file path+name (example- C:\\Users\\User1\\Desktop\\company.dat):  ";
        cin>>companyFilePath;
        iFile.open(companyFilePath.c_str(), ios::binary); 
    }
	
	while (!iFile.eof()){
		getline(iFile, companyNames);
		vecCompanyNames.push_back(companyNames);
		vecPrimaryCompanyNames.push_back(companyNames.substr(0, companyNames.find(delimiter)));
	}
    
    // parse each line of company.dat, identify company names/aliases separated by tab, insert into trie
	for(int i = 0; i<vecCompanyNames.size(); i++){
        companyNames = vecCompanyNames.at(i);
        vector<string> vecSplitCompanyNames = split(companyNames, '\t');
                
        for(int j =0; j< vecSplitCompanyNames.size(); j++){
            trieInstance.insert( vecSplitCompanyNames.at(j), i );
        }		
	}
	
    cout<<"\n\nCompany File read successfully!\n";
    iFile.close();
    Sleep(1500);
    
    cout <<"\n\nEnter article file path+name (example- C:\\Users\\User1\\Desktop\\article.txt):  " ;
	cin>>articleFilePath;
        
    // opeen file company.dat and read it    
    iFile.open(articleFilePath.c_str()); 
    while(!iFile.is_open()){
        cout<<"\n\nFile open failed. Try again!";
        cout<<"\n\nEnter full article file path+name (example- C:\\Users\\User1\\Desktop\\article.txt):  ";
        cin>>articleFilePath;
        iFile.open(articleFilePath.c_str(), ios::binary); 
    }

	while(iFile.get(inputchar)){
        if(inputchar==EOF){
            break;
        }
        createCompanyName = createCompanyName + inputchar;
	}	

    cout<<"\n\nArticle file read successfully!\n";
    iFile.close();
    Sleep(1500);
	
	vecSearchCompanyNames = split(createCompanyName, '\n');
					
	for(int i =0; i < vecSearchCompanyNames.size(); i++){
        vecBreakCompanyNames = split(vecSearchCompanyNames.at(i), ' '); 

        // to ensure we can handle blank lines
        if(vecBreakCompanyNames.size()>1){ 
            //detect company names
            for(int j =0; j < vecBreakCompanyNames.size(); j++){
                specialChar = vecBreakCompanyNames.at(j)[0];
                
                // exclude articles a, an, the, and, or, but when counting total words in article file.
                if(excludeArticles(vecBreakCompanyNames.at(j))){
                    // exclude single special chars
                    if(vecBreakCompanyNames.at(j).length() > 1 || isalpha(specialChar) || isdigit(specialChar)){
                        TotalWordCount = TotalWordCount + 1;
                    }
                }
                
                // detect one word company names
				
				string CompanyNamewithApos = vecBreakCompanyNames.at(j);
								
				CompanyNamewithoutApos = CompanyNamewithApos.substr( 0, CompanyNamewithApos.find("'") ) ;
								
				if(CompanyNamewithoutApos.length() < CompanyNamewithApos.length()){
				searchResultApos = trieInstance.search(CompanyNamewithoutApos);
				}
				
                searchResult = trieInstance.search(vecBreakCompanyNames.at(j));
                if(searchResult == true){
                    continue;
                }
                
                //detect two word company names
                int k = j;
                if(k+1<vecBreakCompanyNames.size()){
                    createCompanyName2words = vecBreakCompanyNames.at(k) + " " + vecBreakCompanyNames.at(k+1);														
                    searchResult = trieInstance.search(createCompanyName2words);
                }
                if(searchResult == true){
                    continue;
                }

                //detect three word company names
                k = j;
                if(k+2<vecBreakCompanyNames.size()){
                    createCompanyName3words = vecBreakCompanyNames.at(k) + " " + vecBreakCompanyNames.at(k+1) + " " + vecBreakCompanyNames.at(k+2);														
                    searchResult = trieInstance.search(createCompanyName3words);
                }
                if(searchResult == true){
                    continue;
                }
                
                //detect four word company names
                k = j;
                if(k+3<vecBreakCompanyNames.size()){
                    createCompanyName4words = vecBreakCompanyNames.at(k) + " " + vecBreakCompanyNames.at(k+1) + " " + vecBreakCompanyNames.at(k+2) + " " + vecBreakCompanyNames.at(k+3);														
                    searchResult = trieInstance.search(createCompanyName4words);
                }
                if(searchResult == true){
                    continue;
                }
            }
        }
        
        //handling period line and single word lines
        else if(vecBreakCompanyNames.size() == 1){
            PeriodLine = vecSearchCompanyNames.at(i);
            
            if(PeriodLine.length() == 1){
                continue;
            }
            
            else{
                for(int k = 0; k< PeriodLine.length(); k++){
                    char periodchar = PeriodLine[k];
                    
                    if((char) periodchar == '.'){
                        isLinePeriod = true;
                    }
                    else{
                        isLinePeriod = false;
                        break;
                    }
                }
                            
                if(!isLinePeriod){
                    if(excludeArticles (PeriodLine)){
                        TotalWordCount = TotalWordCount + 1;
                    }
                    searchResult = trieInstance.search(PeriodLine);
                }
                
                else{
                    break;
                }
            }
        }
        
        // handling a line with white spaces only
        else{
            continue;
        }		
	}
	
	cout << "\n\n\n" <<setw(40) << left << "Company Name" << setw(5) << left << "Hit Count"  << setw(15) <<right <<  "Relevance" <<"\n";
	cout << "\n";
	
	for(int i = 0 ; i < vecPrimaryCompanyNames.size(); i++){
		TotalHitCount = TotalHitCount + CountCompanyOccurrence[i];
		relevance = (float) (CountCompanyOccurrence[i]*100) / TotalWordCount ;
	    TotalRelevance = TotalRelevance + relevance;
		
		cout << "\n" << setw(40) << left << vecPrimaryCompanyNames.at(i) << setw(5) << left << CountCompanyOccurrence[i]  << setw(17) << right << relevance << "%" <<"\n";
    }
	
	cout <<"\n"<< setw(10) <<"       Total Hits " << setw(10) << "Total Relevance\n";
	cout << "\n"<< "Total " << setw(6) << TotalHitCount <<"     "<< setw(10) << (float) TotalRelevance << "%" << "\n";
	cout << "\nTotal Word Count : " << TotalWordCount << "\n";
	Sleep(6000);
	
    cout<< "\nExiting program ...";
	Sleep(3000); 
    exit(EXIT_SUCCESS);
    return 0;
}
