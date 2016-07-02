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
 * \param[in] : root - pointer to a root node
 * \param[out]: none
 * \return    :none
 */
void display_and_process_user_menu(ROOT *root,
                                   char *input_file, 
                                   char *output_file); 

/*! 
 * \brief This function is used to create a new event based
 *        on input from the user 
 * \param[in] : none
 * \param[out]: none
 * \return    :bool - true if adding event was successful
 *                  - false if adding event failed 
 */
bool add_event(ROOT*, char *input_file, char *output_file); 

/*! 
 * \brief Process the event name entered by user 
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : none
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
 * \param[in] : none
 * \param[out]: none
 * \return    : none
 */
bool process_new_event_desc(char* e_desc);


/*! 
 * \brief This function is used to modify an existing event based
 *        on input from the user 
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool - true if name is valid per requirements
 *                 false is name is invalid per requirements 
 */
bool modify_event(ROOT *root,char *input_file, char *output_file); 

/*! 
 * \brief Display the "modify event" user menu 
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
bool display_modify_event_menu();

/*! 
 * \brief Utility function to create a regular node
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
NODE* make_node(EVENT *event);

/*! 
 * \brief Utility function to create an event 
 * 
 * \param[in] : none
 * \param[out]: none 
 * \return    : pointer to EVENT
 */
EVENT* make_event(EVENT* user_event);

/*! 
 * \brief Utility function to create a ROOT node
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
ROOT* make_root();

/*! 
 * \brief Utility function to insert event at head
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
bool insert_at_head(ROOT *root,EVENT *event); 

/*! 
 * \brief Utility function to insert event at tail
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
bool insert_at_tail(ROOT *root,EVENT *user_event); 

/*! 
 * \brief Utility function to insert event at a particular position
 *        based on user_event 
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
bool insert_at_position(ROOT *root,EVENT *user_event); 

/*! 
 * \brief Utility function to print events
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : void
 */
void print_all_events(ROOT *root);

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
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
bool delete_event(ROOT *root, char *input_file, char *output_file);

/*! 
 * \brief Utility function to search event by name
 * 
 * \param[in] : pointer to ROOT
 * \param[out]: none
 * \return    : bool
 */
EVENT* search_by_event_name(ROOT *root);

/*! 
 * \brief Utility function to find event
 * 
 * \param[in] : none
 * \param[out]: none
 * \return    : bool
 */
EVENT* find_event(ROOT* root,EVENT* search_event);

/*! 
 * \brief function to receive and process start time 
 * 
 * \param[in] : pointer to EVENT
 * \param[out]: none
 * \return    : bool
 */
bool process_new_event_start_time(EVENT *user_event);

/*! 
 * \brief function to receive and process end time 
 * 
 * \param[in] : pointer to EVENT
 * \param[out]: none
 * \return    : bool
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
 * \brief function to compare time 
 * 
 * \param[in] : pointer to EVENT
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
 * 
 * \param[in] : pointer to ROOT
 * \param[out]: none
 * \return    : return true if event added to file
 */
bool insert_in_file(ROOT* root,char* input_file, char* output_file);

