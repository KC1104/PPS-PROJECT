from tabulate import tabulate
from matplotlib import pyplot as plt
def event_list():
    print("List of events")
    if event==[]:
        print("No events yet")
    else:
        print(tabulate(event,headers="firstrow",tablefmt="grid"))

global event
event=[["S.No","Event Name","Event Date"],[1,"Python Workshop","20/11/2024"]]
attendee=[["Kushagra Chandra",'kc@gmailcom','Non-Vegetarian','False','Python Workshop']]
event_list()
event_choice=input("Want to add more events(Y/N):")
event_choice=event_choice.lower()
if event_choice=='y':
    print()
    event_name=input("Enter event name:")
    event_date=input("Enter event date(DD/MM/YYYY):")
    m=event[-1][0]
    event.append([m+1,event_name,event_date])
    print(event)
    print()
    event_list()

event_selection=int(input("Enter S.No of the event you want to see details of: "))
print('Event selected',event[event_selection][1])

event_attendee=[['S.No','Name','Email ID','Preference','Attended']]
#MENU
while True:
    print()
    ch=int(input('Enter 1 to see attendee details\nEnter 2 to add attendee\nEnter 3 to mark attendance\nEnter 4 to search for attendee\nEnter 5 to get event summary\nEnter 6 to exit form the menu: '))
    print()
    if ch==1:
        event_attendee=[['S.No','Name','Email ID','Preference','Attended']]
        j=1
        for i in attendee:
            if i[-1]==event[event_selection][1]:
                event_attendee.append(i[0:-1])
                event_attendee[j].insert(0,len(event_attendee)-1)
                j+=1
        if len(event_attendee)!=1:
            print(tabulate(event_attendee,headers='firstrow',tablefmt='grid'))
        else:
            print("No Attendees in the event")
    
    elif ch==2:
        print()
        naam=input('Enter Attendee Name: ')
        per=input('Enter Attendee Preference(Veg/Non-Veg): ')
        email=input('Enter Attendee mail id: ')
        attendance=input('Present in event or not(Y/N): ')
        attendance=attendance.lower()

        if attendance=='y':
            attendee.append([naam,email,per,'True',event[event_selection][1]])
        else:
            attendee.append([naam,email,per,'False',event[event_selection][1]])
    
    elif ch==3:
        x=1
        print('List of Attendees not present:')
        abs=[['S.No','Name','Email ID','Preference','Attended']]
        for i in attendee:
            if i[-1]==event[event_selection][1] and i[-2]=='False':
                abs.append(i[0:-1])
                abs[x].insert(0,len(abs)-1)
                x+=1
        print(tabulate(abs,headers='firstrow',tablefmt='grid'))
        while True:
            att_sl=int(input('\nType Serial No. of the Attendee to mark present(0 to exit): '))
            if att_sl==0:
                break
            else:
                for i in attendee:
                    if i[0]==abs[att_sl][1] and i[-1]==event[event_selection][1]:
                        i[-2]='True'
                        print('Attendance marked for',abs[att_sl][1])
    elif ch==4:
        search=input('Enter Attendee name you want to search(Pls write correct spelling): ')
        found=False
        for i in attendee:
            if i[0].lower().startswith(search.lower()):
                if i[-1]==event[event_selection][1]:
                    print("Attendee",search,' is found')
                    det=input('Do you want to know the details(Y/N): ')
                    if det.lower()=='y':
                        details=[['Name','Email','Preference','Attended','Event']]
                        details.append(i)
                        print(tabulate(details,headers='firstrow',tablefmt='grid'))
                    found=True
                    break
        if not found:
            print('Attendee',search,'not found')
    elif ch==5:
        count=0
        n=0
        v=0
        p=0
        for i in attendee:
            if i[-1]==event[event_selection][1]:
                count+=1
                if i[-2]=='True':
                    p+=1
                if i[2].lower().startswith('non'):
                    n+=1
                else:
                    v+=1
        x=['Total No. of Attendee','Veg Preference','Non-Veg Preference','Present in Event']
        y=[count,v,n,p]
        plt.figure(figsize=(8, 6))
        plt.bar(x,y)
        plt.show() 
        print('Total No. of attendees in the Event',event[event_selection][1],'are:',count)
        print('No. of attendees with Veg preference are:',v)
        print('No. of attendees with Non-Veg preference are:',n)
        print('Attendance percentage:',(p/count)*100,'%')
        
    elif ch==6:
        print('Thank you for using our program\nHave a nice day :)')
        break
                
            
