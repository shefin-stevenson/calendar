    ofile = fopen(argv[1],"w");
                
                EVENT *sample; 
                sample = make_event(sample);
                
                strcpy(sample->event_name,"ENPMProject#");
                
                sample->start_time.month = 04;
                sample->start_time.day   = 25;
                sample->start_time.hour  = 00;
                sample->start_time.min   = 00;
                
                sample->end_time.month   = 05;
                sample->end_time.day     = 18;
                sample->end_time.hour    = 23;
                sample->end_time.min     = 59;
                
                strcpy(sample->event_desc, "This is a great Project#");
                
                fprintf(ofile,"%s\n%02d\\%02d %02d:%02d\n%02d\\%02d %02d:%02d\n%s\n\n",
                        sample->event_name,
                        sample->start_time.month,
                        sample->start_time.day,
                        sample->start_time.hour,
                        sample->start_time.min,
                        
                        sample->end_time.month,
                        sample->end_time.day,
                        sample->end_time.hour,
                        sample->end_time.min,
                        
                        sample->event_desc);
                        
                        
                strcpy(sample->event_name,"This is my second event#");
                
                sample->start_time.month = 03;
                sample->start_time.day   = 31;
                sample->start_time.hour  = 20;
                sample->start_time.min   = 59;
                
                sample->end_time.month   = 12;
                sample->end_time.day     = 14;
                sample->end_time.hour    = 13;
                sample->end_time.min     = 27;
                        
                strcpy(sample->event_desc, "This is the first line\nThis is the second line#");
                        
                fprintf(ofile,"%s\n%02d\\%02d %02d:%02d\n%02d\\%02d %02d:%02d\n%s\n\n",
                        sample->event_name,
                        sample->start_time.month,
                        sample->start_time.day,
                        sample->start_time.hour,
                        sample->start_time.min,
                        
                        sample->end_time.month,
                        sample->end_time.day,
                        sample->end_time.hour,
                        sample->end_time.min,
                        
                        sample->event_desc);
                
                //fwrite(sample, sizeof(EVENT),1,ofile);
                
                fclose(ofile);
                
                ofile = fopen(argv[1],"r+");
                
                int smonth=0;
                int sday=0;
                int shour=0;
                int smin=0;
                int emonth=0;
                int eday=0;
                int ehour=0;
                int emin=0;
                char name[18];
                char desc[256];
                
                int status = fscanf(ofile,"%s\n%02d\\%02d %02d:%02d\n%02d\\%02d %02d:%02d\n%[^\n]s\n\n",
                              &name,&smonth,&sday,&shour,&smin,&emonth,&eday,&ehour,&emin,&desc);
                              
                printf("fopen returned status:%d\n\n",status);
                
                printf("%s\n%02d\\%02d %02d:%02d\n%02d\\%02d %02d:%02d\n%s",
                        name,smonth,sday,shour,smin,emonth,eday,ehour,emin,desc);
                        
                status = fscanf(ofile,"%[^\n]s\n%02d\\%02d %02d:%02d\n%02d\\%02d %02d:%02d\n%[^\n]s\n\n",
                              &name,&smonth,&sday,&shour,&smin,&emonth,&eday,&ehour,&emin,&desc);
                              
                printf("fopen returned status:%d\n\n",status);
                
                printf("%s\n%02d\\%02d %02d:%02d\n%02d\\%02d %02d:%02d\n%s",
                        name,smonth,sday,shour,smin,emonth,eday,ehour,emin,desc);
                             
                fclose(ofile);               
        }
        
        
        
        ---------------------------------------------------------------------------------------
        
        
        FILE *ofile, *ifile; /* pointer to output.cal and input.cal */
        
        if (argv[1] != NULL) {
                
                printf("\n\t%s file present\n\n",argv[1]);
                
                ofile = fopen(argv[1],"rw");
                
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
                //size_t len;
                //char *newline = NULL;
                /* read file until you reach the end of file*/
                
                memset(buffer,0,sizeof(buffer));
                
                while(fgets(buffer, sizeof(buffer), ofile) != NULL) {
                        //printf("\n\tfgets read:%s", buffer);
                
                        if (buffer[0] == '\n') {
                                printf("\n\tNew Line detected\n\n");
                                line_num = 0;
                                continue;
                        }
                        
                        printf("\tLine number:%d",line_num);
                                                
                        switch (line_num % 4) {
                        case 0:
                                if (sscanf(buffer,"%s",&name) != 0) {
                                        printf("\n\tEvent name:%s\n", name);
                                }
                                break;
                                
                        case 1:
                                if(sscanf(buffer,"%02d\\%02d %02d:%02d",&smonth,&sday,&shour,&smin) >= 4){
                                        printf("\n\tStart time:%02d\\%02d %02d:%02d\n",smonth,sday,shour,smin);
                                }
                                break;
                                            
                        case 2: 
                                if(sscanf(buffer,"%02d\\%02d %02d:%02d",&emonth,&eday,&ehour,&emin) >= 4) {
                                        printf("\n\tEnd time:%02d\\%02d %02d:%02d\n",emonth,eday,ehour,emin);
                                }
                                break;
                        
                        case 3:
                                //char *ptr;
                                //ptr = desc;
                                printf("\n\tfgets read:%s\n", buffer);
                                
                                strcpy(desc,buffer);
                                
                                while(strchr (buffer,'#') == NULL) {
                                        char *ptr = desc;
                                        ptr = ptr + strlen(ptr);
                                        if(fgets(buffer, sizeof(buffer), ofile) != NULL) {
                                                printf("\n\tfgets read:%s\n", buffer);
                                                
                                                strcpy(ptr,buffer);
                                        }
                                }
                                printf("%s",desc);
                        
                        
                        
                        #if 0
                                if (sscanf(buffer,"%[^\n]s",&desc) != 0) {
                                         
                                        char *ptr = desc;
                                        
                                        while(strchr (buffer,'#') == NULL) {
                                                ptr = ptr + strlen(ptr);
                                                if(fgets(buffer, sizeof(buffer), ofile) != NULL) {
                                                        printf("\n\tfgets read:%s", buffer);
                                                        sscanf(buffer,"%[^\n]s",ptr);
                                                }
                                        }
                                                                                
                                        printf("\n\tEvent desc:%s\n\n", desc);
                                }
                        #endif         
                                break;
                                                    
                        }
                        
                        line_num++;
                                             
                        memset(buffer,0,sizeof(buffer));
                }
                
                //printf("\n\t event read...\n");
                //printf("%s\n%02d\\%02d %02d:%02d\n%02d\\%02d %02d:%02d\n%s",
                //        name,smonth,sday,shour,smin,emonth,eday,ehour,emin,desc);
                
                fclose(ofile);
        }
        
        exit(1);
