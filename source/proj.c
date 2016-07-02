/*
*
*@main   ENPM-615 Project: Personal Calendar with Linked List. This is
*        project on how to use linked list to implement a personal 
*        calendar that stores all the user's events in year 2016
* 
*@author Shefin Stevenson
* 
*@date   05-21-2016 
*
*/

/* header includes */
#include <stdio.h>    /* standard input output */
#include <stdlib.h>   /* general utilities */
#include <stdbool.h>  /* define bool */ 
#include <string.h>   /* string functions */
#include <ctype.h>    /* check if character is alphanumeric */ 
#include <time.h>     /* time functions */ 

/* Assume events are in 2016 */
#define YEAR 2016

#define SIZE_OF_EVENT_NAME 18

#define SIZE_OF_EVENT_DESC 258

#define MONTH_MIN 01
#define MONTH_MAX 12

#define DAY_MIN 01

#define HOURS_MIN 00 
#define HOURS_MAX 23

#define MINUTES_MIN 00 
#define MINUTES_MAX 59 

/* days in 2016 months */
const int month_days[] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
 
/* structure to hold time */
typedef struct {
        int month;        
        int day;
        int hour;
        int min;
}TIME;

/* EVENT structure */
typedef struct {
        char *event_name; /* name of the event, unique for each event*/
        char *event_desc; /* description of event */ 
        TIME  start_time; /* start time of event */
        TIME  end_time;   /* end time of event */
} EVENT;

/* NODE structure */
typedef struct node{
        EVENT *event;
        struct NODE *next;
} NODE;

/* root structure */
typedef struct {
        long num_nodes;
        NODE *head;
        NODE *tail;
}ROOT; 



/*! 
 * \brief Display user menu and process user input
 * 
 * \param[in] : root - pointer to a root node, 
 *              input_file - name of input file 
 *              output_file - name of output file 
 * \param[out]: none
 * \return    :none
 */
void display_and_process_user_menu(ROOT *root,
                                   char *input_file, 
                                   char *output_file); 

/*! 
 * \brief This function is used to create a new event based
 *        on input from the user 
 * \param[in] : input_file - name of input file
 *              output_file - name of output file  
 * \param[out]: none
 * \return    :bool - true if adding event was successful
 *                  - false if adding event failed 
 */
bool add_event(ROOT*, char *input_file, char *output_file); 

/*! 
 * \brief Process the event name entered by user 
 * 
 * \param[in] : e_name - event name
 * \param[out]: none
 * \return    : true if process succeeded, false if it failed
 */
bool process_new_event_name(char* e_name);

/*! 
 * \brief function to validate event name. An event name consists 
 *        of 0-9, a-z and A-Z and contains no more than 16 characters
 * \param[in] : *e_name - char pointer to event name 
 * \param[out]: none
 * \return    :bool - true if name is valid per requirements
 *                    false is name is invalid per requirements 
 */
bool validate_event_name(char *e_name);

/*! 
 * \brief Process the event description entered by user 
 * 
 * \param[in] : e_desc - event description
 * \param[out]: none
 * \return    : true if process succeeded, false if it failed
 */
bool process_new_event_desc(char* e_desc);


/*! 
 * \brief This function is used to modify an existing event based
 *        on input from the user 
 * \param[in] : root - pointer to a root node, 
 *              input_file - name of input file 
 *              output_file - name of output file 
 * \param[out]: none
 * \return    : true if name is valid per requirements
 *              false is name is invalid per requirements 
 */
bool modify_event(ROOT *root,char *input_file, char *output_file); 

/*! 
 * \brief Display the "modify event" user menu 
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : true if modify succeeded, false if modify failed
 */
bool display_modify_event_menu();

/*! 
 * \brief Utility function to create a regular node
 * 
 * \param[in] : pointer to event
 * \param[out]: none
 * \return    : return a pointer to NODE 
 */
NODE* make_node(EVENT *event);

/*! 
 * \brief Utility function to create an event 
 * 
 * \param[in] : empty pointer to EVENT
 * \param[out]: none 
 * \return    : pointer to memory allocated EVENT
 */
EVENT* make_event(EVENT* user_event);

/*! 
 * \brief Utility function to create a ROOT node
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : pointer to ROOT
 */
ROOT* make_root();

/*! 
 * \brief Utility function to insert event at head
 * 
 * \param[in] : pointer to root, pointer to event
 * \param[out]: none
 * \return    : true if success, false if failure
 */
bool insert_at_head(ROOT *root,EVENT *event); 

/*! 
 * \brief Utility function to insert event at tail
 * 
 * \param[in] : pointer to root, pointer to event
 * \param[out]: none
 * \return    : true if success, false if failure
 */
bool insert_at_tail(ROOT *root,EVENT *user_event); 

/*! 
 * \brief Utility function to insert event at a particular position
 *        based on user_event 
 * 
 * \param[in] : pointer to root, pointer to event
 * \param[out]: none
 * \return    : true if success, false if failure
 */
bool insert_at_position(ROOT *root,EVENT *user_event); 

/*! 
 * \brief Utility function to print events
 * 
 * \param[in] : pointer to root
 * \param[out]: none
 * \return    : void
 */
void print_all_events(ROOT *root);

/*! 
 * \brief Utility function to print time block
 * 
 * \param[in] : pointer to root
 * \param[out]: none
 * \return    : void
 */
void print_time_block(ROOT *root);

/*! 
 * \brief Utility function to print time conflicts
 * 
 * \param[in] : pointer to root
 * \param[out]: none
 * \return    : void
 */
void print_conflicts(ROOT *root);


/*! 
 * \brief Utility function to print an event
 * 
 * \param[in] : event to be printed
 * \param[out]: none
 * \return    : void
 */
void print_event(EVENT *event);
 
/*! 
 * \brief Utility function to print events
 * \param[in] : root - pointer to a root node, 
 *              input_file - name of input file 
 *              output_file - name of output file 
 * \param[out]: none
 * \return    : true if success, false if failure
 */
bool delete_event(ROOT *root, char *input_file, char *output_file);

/*! 
 * \brief Utility function to delete an event
 * \param[in] : root - pointer to a root node, 
 *              input_file - name of input file 
 *              output_file - name of output file 
 * \param[out]: none
 * \return    : true if success, false if failure
 */
bool find_and_delete(ROOT *root,EVENT* del_event,char *input_file, char *output_file);

/*! 
 * \brief Utility function to search event by name
 * 
 * \param[in] : pointer to ROOT
 * \param[out]: none
 * \return    : pointer to EVENT
 */
EVENT* search_by_event_name(ROOT *root);

/*! 
 * \brief Utility function to find event
 * \param[in] : root - pointer to a root node, 
 *              input_file - name of input file 
 * \param[out]: none
 * \return    : pointer to EVENT
 */
EVENT* find_event(ROOT* root,EVENT* search_event);

/*! 
 * \brief function to receive and process start time 
 * 
 * \param[in] : pointer to EVENT
 * \param[out]: none
 * \return    : true if success, false if failureT
 */
bool process_new_event_start_time(EVENT *user_event);

/*! 
 * \brief function to receive and process end time 
 * 
 * \param[in] : pointer to EVENT
 * \param[out]: none
 * \return    : true if success, false if failure
 */
bool process_new_event_end_time(EVENT *user_event);

/*! 
 * \brief function to receive and process end time 
 * 
 * \param[in] : pointer to EVENT
 * \param[out]: none
 * \return    : first EVENT with same start time
 */
EVENT* search_by_start_time(ROOT *root,EVENT *user_event);

/*! 
 * \brief function to search by start time 
 * 
 * \param[in] : pointer to EVENT, pointer to user_event
 * \param[out]: none
 * \return    : none
 */
void search_by_start_and_end_time(ROOT *root,EVENT *user_event);

/*! 
 * \brief function to compare time 
 * 
 * \param[in] : time 1 and time 2 
 * \param[out]: none
 * \return    : return true if same time.
 */
bool is_start_time_identical(TIME time_1 ,TIME time_2);

/*! 
 * \brief function to compare time and return if time_1 is earlier than time_2
 * 
 * \param[in] : pointer to EVENT
 * \param[out]: none
 * \return    : return true if time_1 is earlier than time_2.
 */
bool is_start_time_earlier(TIME time_1 ,TIME time_2);

/*! 
 * \brief function to compare time 
 * 
 * \param[in] : pointer to EVENT
 * \param[out]: none
 * \return    : 0  if t1 = t2;
 *            : -1 if t1 < t2 
 *            : +1 if t1 > t2 
 */
int compare_time(TIME t1, TIME t2);

/*! 
 * \brief function to insert event in a file
 * \param[in] : root - pointer to a root node, 
 *              input_file - name of input file 
 *              output_file - name of output file 
 * \param[out]: none
 * \return    : return true if event added to file
 */
bool insert_in_file(ROOT* root,char* input_file, char* output_file);

/*! 
 * \brief function to process a new event name entered by user for 
*         time conflicts 
 * \param[in] : none
 * \param[out]: none
 * \return    : none
 */
bool process_event_name_conflict(char* e_name);

/*! 
 * \brief function to search conflicts by event name 
 * 
 * \param[in] : pointer to ROOT and pointer to EVENT
 * \param[out]: none
 * \return    : first EVENT with same start time
 */
void search_conflicts(ROOT *root,EVENT *user_event);

/*! 
 * \brief Utility function to search event by keyword in names and description
 * 
 * \param[in] : pointer to ROOT
 * \param[out]: none
 * \return    : void
 */
void search_by_keyword(ROOT *root);


/* main function begins here 
 * Typically the above portion belongs to a header file. As there was only one file 
 * for submission,the header file and souurce file was combined.
 */
int main(int argc, char **argv)
{
        ROOT *root;
        root = make_root();
        EVENT *event;
        event = make_event(event);
        
        FILE *ofile, *ifile; /* pointer to output.cal and input.cal */
                         
        if (argc < 2 || argc > 3) { 
                printf("wrong number of arguments! usage: cal input.cal output.cal || cal output.cal\n");
                exit (1);
        }    
        
        if (argv[1] != NULL && argv[2] == NULL) {
                #if DEBUG
                printf("\n\t input file: %s provided", argv[1]);
                #endif 
        } else if (argv[1] != NULL && argv[2] != NULL) {
 
                ifile = fopen(argv[1],"r");
                
                if (ifile != NULL) {
                        char buffer[SIZE_OF_EVENT_DESC];
                        char name[SIZE_OF_EVENT_NAME];
                        char desc[SIZE_OF_EVENT_DESC];
                        int smonth=0;
                        int sday=0;
                        int shour=0;
                        int smin=0;
                        int emonth=0;
                        int eday=0;
                        int ehour=0;
                        int emin=0;
                        
                        int line_num = 0;
                        memset(buffer,0,sizeof(buffer));
                        
                        
                        while(fgets(buffer, sizeof(buffer), ifile) != NULL) {
                                #if DEBUG
                                printf("\n\tfgets read:%s", buffer);
                                #endif
                        
                                if (buffer[0] == '\n') {
                                        #if DEBUG 
                                        printf("\n\tNew Line detected\n\n");
                                        #endif
                                        line_num = 0;
                                        continue;
                                }
                                
                                #if DEBUG
                                printf("\tLine number:%d",line_num);
                                #endif
                                                        
                                switch (line_num % 4) {
                                case 0:
                                        if (sscanf(buffer,"%s",&name) != 0) {
                                                #if DEBUG
                                                printf("%s\n", name);
                                                #endif
                                        }
                                        break;
                                        
                                case 1:
                                        if(sscanf(buffer,"%02d/%02d %02d:%02d",&smonth,&sday,&shour,&smin) >= 4){
                                                #if DEBUG 
                                                printf("%02d/%02d %02d:%02d\n",smonth,sday,shour,smin);
                                                #endif
                                        }
                                        break;
                                                    
                                case 2: 
                                        if(sscanf(buffer,"%02d/%02d %02d:%02d",&emonth,&eday,&ehour,&emin) >= 4) {
                                                #if DEBUG
                                                printf("%02d/%02d %02d:%02d\n",emonth,eday,ehour,emin);
                                                #endif
                                        }
                                        break;
                                
                                case 3:
                                        #if DEBUG
                                        printf("\n\tfgets read:%s\n", buffer);
                                        #endif 
                                        
                                        strcpy(desc,buffer);
                                        
                                        while(strchr (buffer,'#') == NULL) {
                                                char *ptr = desc;
                                                ptr = ptr + strlen(ptr);
                                                if(fgets(buffer, sizeof(buffer), ifile) != NULL) {
                                                        #if DEBUG 
                                                        printf("\n\tfgets read:%s\n", buffer);
                                                        #endif
                                                        
                                                        strcpy(ptr,buffer);
                                                }
                                        }
                                        #if DEBUG
                                        printf("%s\n\n",desc);
                                        #endif 
                                        
                                        if (name != NULL){
                                                strcpy(event->event_name,name);
                                        }
                                        event->start_time.month = smonth;
                                        event->start_time.day   = sday;
                                        event->start_time.hour  = shour;
                                        event->start_time.min   = smin;
             
                                        event->end_time.month = emonth;
                                        event->end_time.day   = eday;
                                        event->end_time.hour  = ehour;
                                        event->end_time.min   = emin;                            
                                        
                                        if (desc != NULL) {
                                                strcpy(event->event_desc,desc);
                                        }
                                        
                                        insert_at_position(root,event);
                                        
                                        break;
                                                            
                                }
                                
                                line_num++;
                                                     
                                memset(buffer,0,sizeof(buffer));
                        }
                        
                        
                }
                fclose(ifile);
        }
  
        /* Display and process calendar menu options*/
        display_and_process_user_menu(root,argv[1],argv[2]);
        
        return 0; 
}

/*! 
 * \brief Display out the calendar menu to the user 
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    :none
 */
void display_and_process_user_menu(ROOT *root, char* input_file, char* output_file)
{
        char user_input;
        bool display_menu = true;
        EVENT *event; 

        do {
                if (display_menu == true) {
                        /* display message and options to the user */
                        printf("\n\nEnter a number from the list below to select an action, or press 9 to quit\n");
                        
                        printf("\nEdit Commands \n\n");
                        printf("1. Insert new event\n");
                        printf("2. Delete event\n");
                        printf("3. Edit event\n\n");
                        
                        printf(" Print Commands\n\n");
                        printf("4. Print all\n");
                        printf("5. Print time block\n");
                        printf("6. Print conflicts\n\n");
                        
                        printf(" Search Commands\n\n");
                        printf("7. Search by name\n");
                        printf("8. Search by keyword\n");
                }
                
                /* get user input */
                //user_input = getchar();
                //getchar();
                scanf(" %c",&user_input);
                #if 0
                if (user_input == '\n') {
                        getchar();
                }
                #endif
                                                                 
                /* process user input */
                switch (user_input) {
                case '1':
                        add_event(root,input_file,output_file);
                        display_menu = true;
                        break;
                case '2':
                        delete_event(root, input_file,output_file);
                        display_menu = true;
                        break;
                case '3':
                        modify_event(root,input_file,output_file);
                        display_menu = true;
                        break;
                case '4':
                        print_all_events(root);
                        display_menu = true;
                        break;
                case '5':
                        print_time_block(root);
                        display_menu = true;
                        break;
                case '6':
                        print_conflicts(root);
                        display_menu = true;
                        break;
                case '7':
                        event = search_by_event_name(root);
                        print_event(event);
                        display_menu = true;
                        break;
                case '8':
                        search_by_keyword(root);
                        display_menu = true;
                        break;
                case '9':
                        insert_in_file(root,input_file, output_file);
                        return;
                        
                default:
                        printf("Error! please enter an action between 1-9\n");
                        display_menu = false;
                        break;
                }
        }while (user_input != '9');
}
 
/*! 
 * \brief This function is used to create a new event based on user input 
 * \param[in] : none
 * \param[out]: none
 * \return    :bool - true if adding event was successful
 *                  - false if adding event failed 
 */
bool add_event(ROOT *root, char *input_file, char *output_file)
{
        EVENT *event;
        EVENT *event_same_start_time = NULL;
        bool ret_val = false;
        
        event = make_event(event);
        
        /* Request and validate event name */         
        ret_val = process_new_event_name(event->event_name);
        
        if (ret_val == true){
                
                /* Request and validate start time */  
                ret_val = process_new_event_start_time(event);
                
                if (ret_val == true) {
                        
                        /* Request and validate event end time */  
                        ret_val = process_new_event_end_time(event);
                        
                        if (ret_val == true) {
                        
                                /* Request new event description */
                                ret_val = process_new_event_desc(event->event_desc);
                                
                                if (ret_val == true) {
                                        #if 0
                                        event_same_start_time = search_by_start_time(root,event);
                                        
                                        if(event_same_start_time != NULL){
                                                printf("\n\tWarning:%s and %s have the same start time\n",
                                                event_same_start_time->event_name,event->event_name);
                                        }
                                        #endif
                        
                                        //ret_val = insert_at_tail(root,event);
                                        ret_val = insert_at_position(root,event);
                                        
                                        if (ret_val == true) {
                                                ret_val = insert_in_file(root,input_file, output_file);
                                        }
                                        
                                        
                                }
                        }
                }
                #if DEBUG
                printf("\tEvent inserted , Retval:%d\n",ret_val);
                #endif 
                
        }
             
        return ret_val;
} 

/*! 
 * \brief function to process a new event name entered by user
 *        This functions validates and ensures that an event name   
 *        ends with a "#" per requirements. 
 * \param[in] : none
 * \param[out]: none
 * \return    : none
 */
bool process_new_event_name(char* e_name)
{
        bool ret_val = false;
        bool is_valid_name = false;
        size_t name_len = 0; 
        
        do {        
                printf("Enter new event name (no more than 16 characters):");
                scanf("%s",e_name);
                                
                fflush(stdin);

                is_valid_name = validate_event_name(e_name);
                
                if ( is_valid_name == true) {
                        /* get lenth of event name */         
                        name_len = strlen(e_name);
                        #if DEBUG
                        printf("\tUser event name length =%d\n",name_len);
                        #endif
                        
                        /* truncate to 16 chars if length exceeds 16 chars */
                        if (name_len > SIZE_OF_EVENT_NAME-1 ) {
                                //e_name[SIZE_OF_EVENT_NAME-2] = '#'; 
                                e_name[SIZE_OF_EVENT_NAME-1] ='\0';
                        }
                        else {
                                /* event name ends with a # */ 
                                e_name[name_len] = '\0'; 
                        }
                        #if DEBUG        
                        printf("\tEvent name is:%s\n",e_name);
                        #endif
                        
                        ret_val = true; 
                } else { 
                         #if DEBUG
                         printf("\tError! Not a valid event name\n");
                         #endif
                }
        } while (is_valid_name == false);
        
        return ret_val;
}

/*! 
 * \brief function to validate event name. An event name consists 
 *        of 0-9, a-z and A-Z and contains no more than 16 characters
 * \param[in] : *e_name - char pointer to event name 
 * \param[out]: none
 * \return    :bool - true if name is valid per requirements
 *                    false is name is invalid per requirements 
 */
bool validate_event_name(char *e_name)
{
        bool is_valid_event_name = true; 
        
        if (e_name != NULL) {
                size_t len = strlen(e_name);
                int i; 
                 
                /* check whether name is 0-9, a-z and A-Z */
                for (i = 0; (i < len && i < SIZE_OF_EVENT_NAME-2); i++) {
                        if (isalnum(e_name[i]) == 0) {
                                if (e_name[len-1] == '#') {
                                        continue;
                                }
                                is_valid_event_name = false; 
                                break; 
                        }
                }
                
                if (e_name[len-1] != '#') {
                        is_valid_event_name = false;
                }
        }
        else { 
                is_valid_event_name = false;
        }
        
        return is_valid_event_name; 
}

/*! 
 * \brief Process the event description entered by user 
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
bool process_new_event_desc(char* e_desc)
{
        size_t desc_len = 0;
        bool is_valid = true;
        char buf[300]; 
        
        do {
                is_valid = true;
                printf("\nEnter new event description (no more than 256 characters):");
                scanf(" ");
                fgets(buf,300,stdin);
                        
                strcpy(e_desc,buf);
         
                /* get description lenth */         
                desc_len = strlen(e_desc);
                
                #if DEBUG 
                printf("\tEvent lenth is:%d\n",strlen(e_desc));
                #endif
             
                /* truncate if length exceeds 256 */
                if (desc_len > 256) {
                /* event name ends with a # */ 
                        //e_desc[256] = '#'; 
                        e_desc[257] = '\0';
                        
                } else {
                        //e_desc[desc_len-1] = '#'; 
                        e_desc[desc_len-1] = '\0';
                }
                
                if(desc_len == 0 || e_desc[desc_len-2] != '#') {
                        is_valid = false;
                        #if DEBUG 
                        printf("\tError! Not a valid event description\n");
                        #endif
                }
                
        } while (is_valid == false);
        #if DEBUG
        printf("\tEvent description is:%s\n",e_desc);
        #endif
                
        fflush(stdout);
        
        return is_valid;      
}

/*! 
 * \brief function to receive and process start time 
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
bool process_new_event_start_time(EVENT *user_event){
        
        int month=-1;
        int day=-1;
        int hour=-1; 
        int min=-1; 
        int read = -1;
        bool valid_input;

        do {
                printf("\nEnter new event start time (mm/dd hh:mm):");
                
                read = scanf("%d/%d %d:%d",&month, &day, &hour, &min);
                fflush(stdin);
                
                valid_input = true;
                
                if (month < MONTH_MIN || month > MONTH_MAX ){
                        #if DEBUG
                        printf("\n\tError! Incorrect month in a year\n");
                        #endif
                        valid_input = false;
                } else if (day < DAY_MIN || day > month_days[month]) {
                        #if DEBUG
                        printf("\n\tError! Incorrect number of days in a month\n");
                        #endif
                        valid_input = false;
                } else if (hour < HOURS_MIN || hour > HOURS_MAX) {
                        #if DEBUG
                        printf("\n\tError! Incorrect number of hours in a day\n");
                        #endif
                        valid_input = false;
                } else if (min < MINUTES_MIN || min > MINUTES_MAX) {
                        #if DEBUG
                        printf("\n\tError! Incorrect number of minutes in an hour\n");
                        #endif
                        valid_input = false;
                }
        } while (valid_input == false);

        user_event->start_time.month = month;        
        user_event->start_time.day = day;        
        user_event->start_time.hour = hour;        
        user_event->start_time.min = min;

       return true;
}

/*! 
 * \brief function to receive and process end time 
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
bool process_new_event_end_time(EVENT *user_event){
        
        int month=-1;
        int day=-1;
        int hour=-1; 
        int min=-1; 
        int read = -1;
        bool valid_input;

        do {
                printf("\nEnter new event end (mm/dd hh:mm):");
                
                read = scanf("%d/%d %d:%d",&month, &day, &hour, &min);
                fflush(stdin);
                
                valid_input = true;
                
                if (month < MONTH_MIN || month > MONTH_MAX ){
                        #if DEBUG
                        printf("\n\tIncorrect month in a year\n");
                        #endif
                        valid_input = false;
                } else if (day < DAY_MIN || day > month_days[month]) {
                        #if DEBUG
                        printf("\n\tIncorrect number of days in a month\n");
                        #endif
                        valid_input = false;
                } else if (hour < HOURS_MIN || hour > HOURS_MAX) {
                        #if DEBUG
                        printf("\n\tIncorrect number of hours in a day\n");
                        #endif
                        valid_input = false;
                } else if (min < MINUTES_MIN || min > MINUTES_MAX) {
                        #if DEBUG
                        printf("\n\tIncorrect number of minutes in an hour\n");
                        #endif
                        valid_input = false;
                }
        } while (valid_input == false);

        user_event->end_time.month = month;        
        user_event->end_time.day = day;        
        user_event->end_time.hour = hour;        
        user_event->end_time.min = min;

       return true;
}


/*! 
 * \brief This function is used to modify an existing event based
 *        on input from the user 
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool - true if name is valid per requirements
 *                     false is name is invalid per requirements 
 */
bool modify_event(ROOT *root,char *input_file, char *output_file)
{
        EVENT *event = NULL;
        //EVENT *del_event = NULL;
        NODE *temp;
        bool ret_val = false;
        //char name[SIZE_OF_EVENT_NAME];
        
        event = make_event(event);
                
        /* get event name */
        printf("Enter event name to modify:");
        scanf("%s",event->event_name);
                       
        /* attempt to find this event in our list */
        event = find_event(root,event);
        if (event) {
                temp = make_node(event);             
        }
                              
        if (event && temp) {
                
                /* delete old event */
                find_and_delete(root,temp->event,input_file,output_file);
                        
                /* display menu to edit event */
                ret_val = display_modify_event_menu(event);
       
                /* insert new event */
                insert_at_position(root,event);
                
                /* insert modified event back in the file */
                insert_in_file(root,input_file,output_file);
        }

        return ret_val;
}

/*! 
 * \brief Display the "modify event" user menu 
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
bool display_modify_event_menu(EVENT *event)
{
        bool display_menu = true;
        int user_input = 5; 
        bool ret_val = false;
        
        if (event != NULL) 
        {
                 do {
                        //user_input=5;
                        ret_val = false;
                        
                        if (display_menu == true) {
                                printf("Which field would you like to change ?\n");
                                printf("1. Change event name:\n");
                                printf("2. Change start time:\n");
                                printf("3. Change end time:\n");
                                printf("4. Change description");
                        }
                        
                        /* get user input */
                        scanf("%d",&user_input);
                        getchar();
                                               
                        /* process user input */
                        switch (user_input) { 
                        case 1: 
                                ret_val = process_new_event_name(event->event_name);
                                getchar();
                                return ret_val;
                        case 2: 
                                ret_val = process_new_event_start_time(event);
                                getchar();
                                return ret_val;
                        case 3: 
                                ret_val = process_new_event_end_time(event);
                                getchar();
                                return ret_val;                
                        case 4: 
                                ret_val = process_new_event_desc(event->event_desc);
                                return ret_val;
                        
                        default:
                                printf("Error! option between 1-4 expected");
                                display_menu = false;
                                break;        
                        }
                } while (user_input <1 || user_input >4);
        }
        return ret_val;
}

/*! 
 * \brief Utility function to create a node
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
NODE* make_node (EVENT *user_event)
{
        NODE* temp;
        temp = (NODE*) malloc (sizeof(NODE));
        memset(temp,0,sizeof(NODE));
                        
        if (temp != NULL) {
                
                temp->event = (EVENT*) malloc (sizeof(EVENT));
                memset(temp->event,0,sizeof(EVENT));
                
                if (temp->event != NULL) {
                        
                        temp->event->event_name = 
                                (char*)malloc(sizeof(char) * SIZE_OF_EVENT_NAME);
                        memset(temp->event->event_name,'\0',SIZE_OF_EVENT_NAME);
                        strcpy(temp->event->event_name, user_event->event_name);
                        
                        temp->event->event_desc = (char*)malloc(sizeof(char) * SIZE_OF_EVENT_DESC);
                        memset(temp->event->event_desc,'\0',SIZE_OF_EVENT_DESC);
                        strcpy(temp->event->event_desc, user_event->event_desc);
                        
                        temp->event->start_time.month = user_event->start_time.month;
                        temp->event->start_time.day   = user_event->start_time.day;
                        temp->event->start_time.hour  = user_event->start_time.hour;
                        temp->event->start_time.min   = user_event->start_time.min;
                        
                        temp->event->end_time.month = user_event->end_time.month;
                        temp->event->end_time.day   = user_event->end_time.day;
                        temp->event->end_time.hour  = user_event->end_time.hour;
                        temp->event->end_time.min   = user_event->end_time.min;
                        
                        temp->next = NULL;
                        
                }
                else {  /* free allocated memory in case of error */
                        free( temp->event);
                        free(temp);
                }
        }
        return temp; 
}

/*! 
 * \brief Utility function to create an event 
 * 
 * \param[in] : pointer to event
 * \param[out]: none
 * \return    : pointer to EVENT
 */
EVENT* make_event(EVENT* user_event)
{
        /* Allocate memory and initialize event */ 
        user_event = (EVENT*)malloc(sizeof(EVENT));
        memset(user_event,0,sizeof(EVENT));
        
        /* Allocate memory and initialize event name */
        user_event->event_name = (char*)malloc(sizeof(char) * SIZE_OF_EVENT_NAME);
        memset(user_event->event_name,'\0',SIZE_OF_EVENT_NAME);
        
        /* Allocate memory and initialize event description */
        user_event->event_desc = (char*)malloc(sizeof(char) * SIZE_OF_EVENT_DESC);
        memset(user_event->event_desc,'\0',SIZE_OF_EVENT_DESC);
        
        return user_event; 
}

/*! 
 * \brief Utility function to create a ROOT node
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
ROOT* make_root()
{
        ROOT* temp;
        temp = (ROOT*) malloc (sizeof(ROOT));
        memset(temp,0,sizeof(ROOT));
        
        if (temp != NULL) {
                temp->num_nodes = 0;
                temp->head = NULL;
                temp->tail = NULL;
        }
        return temp; 
}


/*! 
 * \brief Utility function to insert event
 * 
 * \param[in] : root - pointer to ROOT 
 * \param[out]: user_event - pointer to EVENT
 * \return    : bool
 */
bool insert_at_head(ROOT *root,EVENT *user_event)
{
        NODE* temp;
        temp = make_node(user_event);
        
        if (temp == NULL) {
                return false;
        }
        
        if (root == NULL) {
                root = make_root();
                if (root == NULL) {
                        return false;
                }
        }
               
        (root->num_nodes)++;
        temp->next = (struct NODE*)root->head;
        root->head = temp;
        
        if (root->num_nodes == 1) {
                root->tail = temp;
        }
        #if DEBUG
        printf("Total number of nodes:%d\n",root->num_nodes);
        #endif
        
        return true;
}

/*! 
 * \brief Utility function to insert event
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
bool insert_at_tail(ROOT *root,EVENT *user_event)
{
        NODE* temp;
        temp = make_node(user_event);
        
        if (temp == NULL) {
                return false;
        }
        
        if (root == NULL) {
                root = make_root();
                if (root == NULL) {
                        return false;
                }
        }
        
        (root->num_nodes)++;
        
        /* if previously the list is empty */
        if (root->num_nodes == 1) {
                root->head = temp;
                root->tail = temp;
        } else {
                root->tail->next = (struct NODE*)temp;
                root->tail = temp;
        }
        #if DEBUG
        printf("\tTotal number of nodes:%d\n",root->num_nodes);
        #endif
        
        return true;
}

/*! 
 * \brief Utility function to insert event at a particular position
 *        based on user_event 
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
bool insert_at_position(ROOT *root,EVENT *user_event)
{
        NODE *temp, *this;
        bool is_earlier = false;
        bool is_same = false;
        
        temp = make_node(user_event);

        if (temp == NULL) {
                return false;  /* Cannot create new NODE */
        }
        
        if (root == NULL) { 
                root = make_root();
                if (root == NULL) {
                        return false;   /* cannot create ROOT */
                }
        }
        
        this = root->head;
        
        /* CASE 1: Insert at head */
        if (this != NULL) {
                //if (*(DATA *)(this->data) <= *(DATA *)(temp->data)) 
                /* start time of new event is earlier than start time of event at head */
                
                int diff = compare_time(temp->event->start_time,this->event->start_time);
                int diff_end_time =  compare_time(temp->event->end_time,this->event->end_time);
                
                //int cmp = strcmp(temp->event->event_name,this->event->event_name);
                
                int name_cmp = strcoll(temp->event->event_name,this->event->event_name);
                                                
                if (diff == -1 || diff == 0) {
                        /* if start time of "user" event is the same as that of the event in the list
                         * then compare end time.
                         */
                        if (diff == 0) { 
                                
                                //printf("start times are same.....\n");
                                
                                printf("Warning:%s and %s have the same start time.\n",
                                        temp->event->event_name,this->event->event_name);
                                
                                /* if end time of "user" event less than existing node ,
                                 * then compare event names*/        
                                if (diff_end_time == -1) {
                                        insert_at_head(root, temp->event);                                        
                                } else if (diff_end_time == 0){
                                        //printf("end times are same.....\n");
                                        
                                        if (name_cmp <= 0) {
                                                //printf("Event names same or sorted lower.....\n");
                                                insert_at_head(root, temp->event);
                                        } else {
                                                insert_at_tail(root, temp->event);// check this case out ???
                                        }
                                } else {                                         // if the user end time is greater ???
                                        //insert_at_tail(root,temp->event);
                                       
                                        /* pointer to access the next of the "this" node */
                                        NODE* ptr = (NODE*)this->next;
                                        
                                        if (ptr != NULL) {
                                                diff = compare_time(temp->event->start_time, ptr->event->start_time);
                                                
                                                diff_end_time =  compare_time(temp->event->end_time,ptr->event->end_time);
                                                
                                        }
                                        
                                        while (ptr != NULL && ((diff == 1 && diff_end_time == 1) || (diff == 0 && diff_end_time == 1)))
                                               // *(DATA *)(this->next->event->start_time) > *(DATA *)(temp->data)) 
                                        {
                                                
                                                /* start time of new event is greater than start time of event at root*/
                                                /* i.e. time of new event is not earlier and not equal to start time of */
                                                             
                                                this = (NODE*)this->next;
                                                ptr = (NODE*)this->next;
                                                
                                                if (ptr != NULL){
                                                        diff = compare_time(temp->event->start_time, ptr->event->start_time);
                                                        diff_end_time =  compare_time(temp->event->end_time,ptr->event->end_time);
                                                
                                                        /* if start time and end time are same, compare the name */
                                                        if (diff == 0 && diff_end_time == 0) {
                                                                name_cmp = strcoll(ptr->event->event_name,temp->event->event_name);
                                                                
                                                                if (name_cmp <=0 ) {
                                                                         this = (NODE*)this->next;
                                                                } 
                                                        }
                                                
                                                }
                                        } 
                                        
                                        /* if start time and end time are same, compare the name */
                                        if (diff == 0 && diff_end_time == 0) {
                                                name_cmp = strcoll(ptr->event->event_name,temp->event->event_name);
                                                
                                                if (name_cmp <=0 ) {
                                                        this = (NODE*)this->next;
                                                } 
                                        }
                                        
                                        // we compare d with this->next->data rather then this->data because
                                        // if this->next->data becomes smaller than d, we want to insert d in
                                        // front of this->next. "this" can be treated as the previous of this->next,
                                        // if we compare d directly with this->data, we cannot retrieve the previous
                                        // of "this".
                                        
                                        //CASE 2: Insert at TAIL
                                        if (this->next == NULL)  {   // update tail if insert at tail
                                                root->tail = temp;
                                                this->next = (struct NODE*)temp;
                                                (root->num_nodes)++;
                                        } else { 
                                                temp->next = this->next;
                                                this->next = (struct NODE*)temp;
                                                (root->num_nodes)++;
                                        }
                                        
                                }
                                                                
                        } else if (diff == -1) {  /* compare start times */
                                insert_at_head(root, temp->event);                                
                        }
                } else {
                        /* pointer to access the next of the "this" node */
                        NODE* ptr = (NODE*)this->next;
                        
                        if (ptr != NULL) {
                                diff = compare_time(temp->event->start_time, ptr->event->start_time);
                        }
                        
                        while (ptr != NULL && (diff == 1))
                               // *(DATA *)(this->next->event->start_time) > *(DATA *)(temp->data)) 
                        {
                        
                                /* start time of new event is greater than start time of event at root*/
                                /* i.e. time of new event is not earlier and not equal to start time of */
                                             
                                this = (NODE*)this->next;
                                ptr = (NODE*)this->next;
                                
                                if (ptr != NULL){
                                        diff = compare_time(temp->event->start_time, ptr->event->start_time);
                                }

                        } 
                       
                        // we compare d with this->next->data rather then this->data because
                        // if this->next->data becomes smaller than d, we want to insert d in
                        // front of this->next. "this" can be treated as the previous of this->next,
                        // if we compare d directly with this->data, we cannot retrieve the previous
                        // of "this".
                        
                        //CASE 2: Insert at TAIL
                        if (this->next == NULL)  {   // update tail if insert at tail
                                root->tail = temp;
                                this->next = (struct NODE*)temp;
                                (root->num_nodes)++;
                        } else { 
                                temp->next = this->next;
                                this->next = (struct NODE*)temp;
                                (root->num_nodes)++;
                        }
                        
                        if (diff == 0) { 
                                printf("Warning:%s and %s have the same start time.\n",
                                        temp->event->event_name,this->event->event_name);
                        }
                }
                
        } else { /* List is empty. Insert at head */
                insert_at_head(root, temp->event);
        }
        
        return true;
}


/*! 
 * \brief Utility function to print events
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
void print_all_events(ROOT *root)
{
        NODE *temp;
        
        if (root != NULL) { 
                temp = root->head;
                
                if (temp != NULL) {
                        #if 0
                        printf("\tTotal number of events:%d\n",root->num_nodes);
                        #endif
                
                        do {
                                printf("%s\n",temp->event->event_name);
                                printf("%02d/%02d %02d:%02d\n",
                                        temp->event->start_time.month,
                                        temp->event->start_time.day,
                                        temp->event->start_time.hour,
                                        temp->event->start_time.min);
                                
                                printf("%02d/%02d %02d:%02d\n",
                                        temp->event->end_time.month,
                                        temp->event->end_time.day,
                                        temp->event->end_time.hour,
                                        temp->event->end_time.min);
                                printf("%s\n\n\n",temp->event->event_desc);
                                
                                temp = (NODE*)temp->next;
                        }while (temp != NULL);
                } else {
                        #if DEBUG
                        printf("\tNo events to display\n");
                        #endif
                }
        } else {
                #if DEBUG
                printf("\tNo events to display\n");
                #endif
        }
        
        getchar();
}

/*! 
 * \brief Utility function to print time block
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : void
 */
void print_time_block(ROOT *root){
        
        EVENT* event;
        EVENT* tevent;
        
        int month=-1;
        int day=-1;
        int hour=-1; 
        int min=-1; 
                        
        event = make_event(event);
            
        printf("Enter a start time (mm/dd hh:mm):");
        scanf("%d/%d %d:%d",&month, &day, &hour, &min);
        
        event->start_time.month = month;
        event->start_time.day = day;
        event->start_time.hour = hour;
        event->start_time.min = min;
        
        
        printf("Enter an end time (mm/dd hh:mm):");
        scanf("%d/%d %d:%d",&month, &day, &hour, &min);
        
        event->end_time.month = month;
        event->end_time.day = day;
        event->end_time.hour = hour;
        event->end_time.min = min;
        
        /* for each NODE, compare start time or end time within this block */
        
        /* first compare start time entered within block */
        /* then compare end time entered within block */
        /* if either time is within block , print event on screen */
        
        search_by_start_and_end_time(root,event);
                
}

/*! 
 * \brief Utility function to print time conflicts
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : void
 */
void print_conflicts(ROOT *root)
{
        EVENT *user_event; 
        user_event = make_event(user_event);
        
        if (process_event_name_conflict(user_event->event_name)) {
               
                user_event = find_event(root,user_event);
        
                search_conflicts(root,user_event);
        }
}


/*! 
 * \brief Utility function to print an event
 * 
 * \param[in] : event to be printed
 * \param[out]: none
 * \return    : void
 */
void print_event(EVENT *event)
{
        if (event != NULL) {
                
                printf("%s\n",event->event_name);
                
                printf("%02d/%02d %02d:%02d\n",
                        event->start_time.month,
                        event->start_time.day,
                        event->start_time.hour,
                        event->start_time.min);
                
                printf("%02d/%02d %02d:%02d\n",
                        event->end_time.month,
                        event->end_time.day,
                        event->end_time.hour,
                        event->end_time.min);
                printf("%s\n\n\n",event->event_desc);
        }
}


/*! 
 * \brief Utility function to search event by name
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
EVENT* search_by_event_name(ROOT *root)
{
        EVENT *search_event = NULL;
        
        search_event = make_event(search_event);
        
        printf("Enter the event name to search for:");
        scanf("%s",search_event->event_name);
        
        search_event = find_event(root,search_event);
 
        return search_event;
}
/*! 
 * \brief Utility function to find event
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
EVENT* find_event(ROOT* root,EVENT* search_event)
{
        NODE* temp;
        bool found = false;
        int cmp = -2;
        
        if(root != NULL && search_event != NULL) {
                temp = root->head;
    
                fflush(stdin);

                if (temp != NULL) {
                        do {
                                /* Is search string in the list */
                                cmp = strcmp(search_event->event_name,
                                              temp->event->event_name);
                                                                            
                                if (cmp == 0) {
                                        found = true;
                                        break;
                                }
                                temp = (NODE*)temp->next;                        
                        } while (temp != NULL);
                } 
        }
         
        if (found == true) {
                #if DEBUG 
                printf("%s found\n",search_event->event_name);     
                #endif
                search_event = temp->event;
        } else {
                printf("%s not found\n",search_event->event_name);
                search_event = NULL;
        }
         
        getchar();
        
        return search_event;
}

/*! 
 * \brief Utility function to print events
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
bool delete_event(ROOT *root,char *input_file, char *output_file)
{
        NODE *temp;
        EVENT *del_event;
        bool found = false;
        NODE *prev;
        int cmp = -1; 
        
        del_event = make_event(del_event);
        
        printf("Enter the event name to be deleted:");
        scanf("%s",del_event->event_name);
        fflush(stdin);

        //strcat(del_event->event_name,"#");
        
        if(root == NULL) {
                printf("Error ! %s not found \n",del_event->event_name);
                
                return found;
        }
                
        temp = root->head;
        prev = root->head;
        
        if (temp != NULL) {
                do {
                        /* Is search string in the list */
                        cmp = strcmp(del_event->event_name,
                                     temp->event->event_name);
                                                            
                        if (cmp == 0) {
                                found = true;
                                break;
                        }
                        prev = temp;
                        temp = (NODE*)temp->next;                        
                } while (temp != NULL);
        }

        if (found == true) {
               
                // case 1: event is at head
                if (temp == root->head) {
                        root->head  = (NODE*)temp->next;
                        (root->num_nodes)--;
                        
                        free(temp);
                                               
                        printf("%s has been deleted",del_event->event_name);
                        
                        
                } else {  /* event is not at head */
              
                        /*  case 2: event is at tail */
                        if (temp->next == NULL) {        
                                root->tail = prev;
                                root->tail->next = temp->next;
                                (root->num_nodes)--;
                                
                                free(temp);
                                
                                printf("%s has been deleted",del_event->event_name);
                                
                        } else {  /* case 3: event is neither the root or the tail */
                                
                                prev->next = temp->next;
                                temp->next = NULL;
                                (root->num_nodes)--;
                                
                                free(temp);
                                
                                printf("%s has been deleted",del_event->event_name);
                                
                        }
                } 
                
                /* update deleted node on file */
                insert_in_file(root,input_file,output_file);
                
        } else {
                printf("Error ! %s not found \n",del_event->event_name);
        }
        
        getchar();
        return found;
}

/*! 
 * \brief Utility function to delete an event
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
bool find_and_delete(ROOT *root,EVENT* del_event,char *input_file, char *output_file)
{
        NODE *temp;
        bool found = false;
        NODE *prev;
        int cmp = -1; 
        
        //del_event = make_event(del_event);

        if(root == NULL) {
                printf("Error ! %s not found (root NULL)\n",del_event->event_name);
                
                return found;
        }
                
        temp = root->head;
        prev = root->head;
        
        if (temp != NULL) {
                do {
                        /* Is search string in the list */
                        cmp = strcmp(del_event->event_name,
                                     temp->event->event_name);
                                                            
                        if (cmp == 0) {
                                found = true;
                                break;
                        }
                        prev = temp;
                        temp = (NODE*)temp->next;                        
                } while (temp != NULL);
        }

        if (found == true) {
               
                // case 1: event is at head
                if (temp == root->head) {
                        root->head  = (NODE*)temp->next;
                        (root->num_nodes)--;
                        
                        free(temp);
                        #if 0                       
                        printf("%s has been deleted",del_event->event_name);
                        #endif
                        
                        
                } else {  /* event is not at head */
              
                        /*  case 2: event is at tail */
                        if (temp->next == NULL) {        
                                root->tail = prev;
                                root->tail->next = temp->next;
                                (root->num_nodes)--;
                                
                                free(temp);
                                #if 0
                                printf("%s has been deleted",del_event->event_name);
                                #endif
                                
                        } else {  /* case 3: event is neither the root or the tail */
                                
                                prev->next = temp->next;
                                temp->next = NULL;
                                (root->num_nodes)--;
                                
                                free(temp);
                                #if 0
                                printf("%s has been deleted",del_event->event_name);
                                #endif
                                
                        }
                } 
                
                /* update deleted node on file */
                insert_in_file(root,input_file,output_file);
                
        } else {
                printf("Error ! %s not found \n",del_event->event_name);
        }
             
        return found;
}

/*! 
 * \brief function to search by start time 
 * 
 * \param[in] : pointer to EVENT
 * \param[out]: none
 * \return    : first EVENT with same start time
 */
EVENT* search_by_start_time(ROOT *root,EVENT *user_event)
{
        NODE *temp;
        bool is_same = false;
        
        if(root != NULL) {
                temp = root->head;
                                    
                if (temp != NULL) {
                        do {
                                /* Compare user entered time with existing event(s) start time */
                                is_same = is_start_time_identical(temp->event->start_time,
                                                       user_event->start_time);  
                                
                                /* if two different events have the same start time , return */                                                                            
                                if (is_same == true && (0 != strcmp(temp->event->event_name,user_event->event_name))) {
                                   break;
                                }
                                temp = (NODE*)temp->next;                        
                        } while (temp != NULL);
                } else {
                        return NULL;
                } 
        } else {
                return NULL;
        }

        return temp->event;
}

/*! 
 * \brief function to compare time 
 * 
 * \param[in] : pointer to EVENT
 * \param[out]: none
 * \return    : return true if same time.
 */
bool is_start_time_identical(TIME time_1 ,TIME time_2)
{
        bool is_same = false;
        
        if (time_1.month == time_2.month) {
                if (time_1.day == time_2.day) {
                        if (time_1.hour == time_2.hour) {
                                if(time_1.min == time_2.min) {
                                        is_same = true;
                                } 
                        }
                }
                
        }
        //printf("\n\t is_start_time_identical:%",is_same);
        return is_same;
}

/*! 
 * \brief function to compare time and return if time_1 is earlier than time_2
 * 
 * \param[in] : pointer to EVENT
 * \param[out]: none
 * \return    : return true if same time.
 */
bool is_start_time_earlier(TIME time_1 ,TIME time_2)
{
        bool is_earlier = false;
        
        if (time_1.month < time_2.month) {
                
                is_earlier = true;
                
        } else if (time_1.month == time_2.month) {
                                
                if (time_1.day < time_2.day) {
                        
                        is_earlier = true;
                        
                } else if (time_1.day == time_2.day) {
                        
                        if (time_1.hour < time_2.hour) {
                                
                                is_earlier = true;
                                
                        } else if (time_1.hour == time_2.hour) {
                                
                                if (time_1.min < time_2.min) {
                                        is_earlier = true;
                                }
                        } 
                        
                }
                
        }
        
        //printf("\n\t is_start_time_earlier:%\n",is_earlier);
        
        return is_earlier;
        
}
/*! 
 * \brief function to compare time 
 * 
 * \param[in] : pointer to EVENT
 * \param[out]: none
 * \return    : 0  if t1 = t2;
 *            : -1 if t1 < t2 
 *            : +1 if t1 > t2 
 */
int compare_time(TIME t1, TIME t2)
{
        int result = -2;
        
        if(is_start_time_identical(t1,t2)) {
                result = 0;
        } else {
                if (is_start_time_earlier(t1,t2)) {
                        result = -1; 
                } else {
                        result = 1;
                }
        }
        
        return result;
}

/*! 
 * \brief function to search by start time 
 * 
 * \param[in] : search and print time blocks
 * \param[out]: none
 * \return    : first EVENT with same start time
 */
void search_by_start_and_end_time(ROOT *root,EVENT *user_event)
{
        NODE *temp;
        bool is_same = false;
        int diff_sa_eb = -2;
        int diff_ea_sb = -2;
        
        
        if(root != NULL) {
                temp = root->head;
                                    
                if (temp != NULL) {
                        do {                                
                                diff_sa_eb = compare_time(temp->event->start_time,user_event->end_time);
                                
                                diff_ea_sb = compare_time(temp->event->end_time,user_event->start_time);
                                
                                if ((diff_sa_eb == 0 || diff_sa_eb == -1) && (diff_ea_sb == 0 || diff_ea_sb == -1)){
                                        
                                       
                                        
                                }
                                else {
                                        print_event(temp->event);
                                }
                                                                  
                                temp = (NODE*)temp->next;                        
                        } while (temp != NULL);
                } else {
                        //return NULL;
                } 
        } else {
                //return NULL;
        }
        
        getchar();
        
}



/*! 
 * \brief function to insert event in a file
 * 
 * \param[in] : pointer to ROOT
 * \param[out]: none
 * \return    : return true if event added to file
 */
bool insert_in_file(ROOT* root,char* input_file, char* output_file)
{
        NODE *temp;
        FILE *handle;
        
        if (input_file != NULL && output_file == NULL) {
                handle = fopen(input_file,"w");
        } else if (input_file != NULL && output_file != NULL) {
                handle = fopen(output_file,"w");
        } else {
                #if DEBUG
                printf("\n\t File handle Error!");
                #endif 
        }
        
        
        if (root != NULL && handle != NULL) { 
                temp = root->head;
                
                if (temp != NULL) {
                        #if DEBUG
                        printf("\tTotal number of events:%d\n",root->num_nodes);
                        #endif
                
                        do {
                                fprintf(handle,"%s\n",temp->event->event_name);
                                fprintf(handle,"%02d/%02d %02d:%02d\n",
                                        temp->event->start_time.month,
                                        temp->event->start_time.day,
                                        temp->event->start_time.hour,
                                        temp->event->start_time.min);
                                
                                fprintf(handle,"%02d/%02d %02d:%02d\n",
                                        temp->event->end_time.month,
                                        temp->event->end_time.day,
                                        temp->event->end_time.hour,
                                        temp->event->end_time.min);
                                fprintf(handle,"%s\n\n\n",temp->event->event_desc);
                                                                                               
                                temp = (NODE*)temp->next;
                        }while (temp != NULL);
                        #if DEBUG
                        printf("\n\inserted event in file ...\n");
                        #endif 
                } else {
                        #if DEBUG
                        printf("\tNo events to write to file\n");
                        #endif
                }
        } else {
                #if DEBUG 
                printf("\tNo events written\n");
                #endif 
        }
        
        fclose(handle);
       
        return true;
}

/*! 
 * \brief function to process a new event name entered by user
 *        This functions validates and ensures that an event name   
 *        ends with a "#" per requirements. 
 * \param[in] : none
 * \param[out]: none
 * \return    : none
 */
bool process_event_name_conflict(char* e_name)
{
        bool ret_val = false;
        bool is_valid_name = false;
        size_t name_len = 0; 
        
        do {        
                printf("Enter the event name:");
                scanf("%s",e_name);
                                
                fflush(stdin);

                is_valid_name = validate_event_name(e_name);
                
                if ( is_valid_name == true) {
                        /* get lenth of event name */         
                        name_len = strlen(e_name);
                        #if DEBUG
                        printf("\tUser event name length =%d\n",name_len);
                        #endif
                        
                        /* truncate to 16 chars if length exceeds 16 chars */
                        if (name_len > SIZE_OF_EVENT_NAME-1 ) {
                                //e_name[SIZE_OF_EVENT_NAME-2] = '#'; 
                                e_name[SIZE_OF_EVENT_NAME-1] ='\0';
                        }
                        else {
                                /* event name ends with a # */ 
                                e_name[name_len] = '\0'; 
                        }
                        #if DEBUG        
                        printf("\tEvent name is:%s\n",e_name);
                        #endif
                        
                        ret_val = true; 
                } else { 
                         #if DEBUG
                         printf("\tError! Not a valid event name\n");
                         #endif
                }
        } while (is_valid_name == false);
        
        return ret_val;
}

/*! 
 * \brief function to search conflicts by event name 
 * 
 * \param[in] : search and print time blocks
 * \param[out]: none
 * \return    : first EVENT with same start time
 */
void search_conflicts(ROOT *root,EVENT *user_event)
{
        NODE *temp;
        bool is_same = false;
        int diff_sa_eb = 10;
        int diff_sb_ea = 10;
        bool found_conflicts = false;
        
        
        if(root != NULL) {
                temp = root->head;
                                    
                if (temp != NULL) {
                        do {    
                                if (strcmp(temp->event->event_name,user_event->event_name) != 0) {
                                                            
                                        diff_sa_eb = compare_time(temp->event->start_time,user_event->end_time);
                                        
                                        diff_sb_ea = compare_time(user_event->start_time,temp->event->end_time);
                                        
                                        if ((diff_sa_eb <= 0 ) && (diff_sb_ea  <= 0)){
                                                
                                               print_event(temp->event);
                                               found_conflicts = true;
                                                
                                        }
                                                                          
                                       
                                } 
                                
                                temp = (NODE*)temp->next;                       
                        } while (temp != NULL);
                } else {
                        //return NULL;
                } 
        } else {
                //return NULL;
        }
        
        if (found_conflicts == false) {
                printf("No conflicting event.\n");
        }
        
}

/*! 
 * \brief Utility function to search event by keyword in names and description
 * 
 * \param[in] : pointer to ROOT
 * \param[out]: none
 * \return    : pointer to EVENT
 */
void search_by_keyword(ROOT *root)
{
        char keyword[50];
        memset(keyword,0,sizeof(keyword));
        
        NODE *temp;
        
        printf("Enter a keyword to search for:");
        scanf("%s",keyword);
        
        char *token = NULL;
        
        token = strstr(keyword,"#");
        
        /* remove token is present in input */
        if(token){
             keyword[strlen(keyword)-1] = '\0';   
        }
     
        if(root != NULL && keyword != NULL) {
                temp = root->head;
                                    
                if (temp != NULL) {
                        do {    
                      
                                char *key_in_name = NULL; 
                                char *key_in_description = NULL;
                                
                                key_in_name = strstr(temp->event->event_name,keyword);
                                
                                if (key_in_name == NULL) {
                                        key_in_description = strstr(temp->event->event_desc,keyword);
                                }
                                                            
                                if ((key_in_name) || (key_in_description)){
                                        
                                       print_event(temp->event);
                                                                          
                                }
                                
                                temp = (NODE*)temp->next;                       
                        } while (temp != NULL);
                } 
        }      
}
