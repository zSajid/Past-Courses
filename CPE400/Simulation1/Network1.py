# This is a program for a networking homework assignment
# Start from 0, and head all the way to 1000
import random

# Global variables
packagesGeneratedAtTimeT = [];

#Intialize the set packets with values of 0
for i in range(1001):
    packagesGeneratedAtTimeT.append(0);



print("Part 4, problem a")
for i in range(0, 1001):
    # Go from 0 to 35 individuals
    for y in range(0, 36):
        # Create a random number from 0 to 100
        randomNumber = random.randint(0, 101);

        # If random number divided by /100 is greater than 40, then place that packet on the array
        if (randomNumber <= 40):
            # Append the users value if a package was generated
            packagesGeneratedAtTimeT[i] = packagesGeneratedAtTimeT[i] + 1;

        # Else, just abandon it
        else:
            pass;

#Intialize the set packets with values of 0
total = 0;
for i in range(1001):
    total = total + packagesGeneratedAtTimeT[i];


print(str(total) + ' packages were generated during this 1000 time slot ');


#Packet counter for time slot
NumberOfPackets= [];

#Intialize the set packets with values of 0
for i in range(36):
    NumberOfPackets.append(0);

for i in range(0, 1001):
    for y in range(0, 36):
        if(packagesGeneratedAtTimeT[i] == y):
            NumberOfPackets[y] +=1;


print(str(NumberOfPackets[10])+" this is value of k = 10");
print(str(NumberOfPackets[15])+" this is value of k = 15");
print(str(NumberOfPackets[20])+" this is value of k = 20");

for i in range(0, 36):
    print(str(NumberOfPackets[i]) + " this is value of k = " + str(i));


########################################################################################################################
#Part 4
print("Part 4, problem d, how many packets were lost, and the fraction");


#Reset all the values to 0;
for i in range(1001):
    packagesGeneratedAtTimeT[i] = 0;


#This will be a counter for the packets lost
packetLost = 0;

for i in range(0, 1001):
    # Go from 0 to 35 individuals
    for y in range(0, 36):
        # Create a random number from 0 to 100
        randomNumber = random.randint(0, 101);

        # If random number divided by /100 is greater than 40, then place that packet on the array
        if (randomNumber <= 40):
            if(packagesGeneratedAtTimeT[i] >= 18):
                 packetLost += 1;


            else:
                #Append the users value if a package was generated
                packagesGeneratedAtTimeT[i] = packagesGeneratedAtTimeT[i] + 1;


total = 0;
for i in range(1001):
    total = total + packagesGeneratedAtTimeT[i];
print(str(total) + ' packages were generated during this 1000 time slot ');
print(str(packetLost) + ' packages were thrown away during this interval');
