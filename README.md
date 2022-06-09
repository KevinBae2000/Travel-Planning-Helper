## _22000323, Bae Byungju_

Project name: Travel Planning Helper

Youtube link: 

## What does this project do?
The user first enters the traffic budget and selects the current location. The program shows the area where you can go from that location, and the user chooses the area you want to go. The program then shows the means of transportation, each price and time. If the user chooses, the program will show the remaining budget, and ask users to continue traveling to another area. If the total cost exceeds the traffic budget after the user chooses the means of transportation, the program tells the user that transportation costs exceeded the budget. After finishing the plan, the program shows and make textfile about the total transportation cost and time and tourist attractions in each area that user decided to go.

## Why is this project useful?
If you move without planning when you travel in Korea, traffic expenses often exceed traffic budgets, and sometimes you take too much traffic time. The program prevents that situation, and show time and money to spend on total transportation, and informs tourist attractions in the travel area. Finally, you can receive your total plan as a text file.

## How do I get started?
There are 4 files(main.c, list.txt, place.txt, travel.txt) in total.
> main.c: C code file
> 
> list.txt: Text files for transportation, use weight value (First, Second numbers are 1. Jeonju 2. Seoul 3. Busan 4. Ulsan 5. Daejeon 6. Suwon. Third number is 1. Train 2. Bus 3. Airplane)
> 
> place.txt: Text files for tourist attractions, use weight value (First numbers is 1. Jeonju 2. Seoul 3. Busan 4. Ulsan 5. Daejeon 6. Suwon)
> 
> travel.txt: Text files for result

0. Complile main.c file
ex) $ g++ main.c -o main.o

1. Run main.o file.
ex) $ ./main.o

2. Type Budget and select starting point.

![image](https://user-images.githubusercontent.com/103616973/172415349-1d6893a4-264e-4545-b1e1-cf1a699233bd.png)


3. Select place to travel and trasportation to use.

![image](https://user-images.githubusercontent.com/103616973/172416038-03d6da83-b2ce-483b-b67c-92d4d9b27190.png)

4. Choose whether or not you plan to go to the next area for trip.

![image](https://user-images.githubusercontent.com/103616973/172417122-76e6ea37-9abb-422b-a83f-6e6ba49c49a2.png)

![image](https://user-images.githubusercontent.com/103616973/172417306-891fe5fb-d3e8-43c3-aa0b-7b935e604c0e.png)

5. Show result and make text file when you finished.

![image](https://user-images.githubusercontent.com/103616973/172417623-12cda5c2-dc21-4f89-ab4c-f69f19b481d8.png)

![image](https://user-images.githubusercontent.com/103616973/172417755-74835d73-2f27-424a-a41c-1c92fc69613d.png)

## Where can I get more help, if I need it?

If you have any questions or would like more information, please contact at 22000323@handong.ac.kr.

## My contribution

I wrote the full codes.
