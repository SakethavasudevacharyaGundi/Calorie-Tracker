#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_ITEMS 5
#define INCREMENT_SIZE 5

void printUserDataFromFile(char *name);
void breakfast();
void lunch();
void dinner();
void exerciseMenu();
void mainMenu();
void calorieMenu();
float calculateCalories(char exercise[]);
float totalExercises = 0;


void addFoodItems(char foodName[], float calories) {
    FILE *foodList;
    foodList = fopen("foodlist.txt", "a");
    fprintf(foodList, "%s %f\n", foodName, calories);
    fclose(foodList);
}

float calculateTotalCaloriesIntake() {
    FILE *foodList;
    float totalCalories = 0.0;
    char foodName[50];
    float calories;

    foodList = fopen("foodlist.txt", "r");
    if (foodList == NULL) {
        printf("Error: File could not be opened.\n");
        return 0.0;
    }

    while (fscanf(foodList, "%s %f", foodName, &calories) != EOF) {
        totalCalories += calories;
    }

    fclose(foodList);
    return totalCalories;
}

typedef struct {
  float height;
  float weight;
  char name[100];
  int check;
} userdata;

typedef struct {
  char name[50];
  float calories;
} FoodItem;

userdata checkname[100];
int count = 0;
void save() {
  FILE *file = fopen("userdata.txt", "a");

  if (file == NULL) {
    printf("Error opening the file.\n");
    return;
  }

  for (int i = 0; i < count; i++) {
    fprintf(file, "%s %.2f %.2f\n", checkname[i].name, checkname[i].height,
            checkname[i].weight);
  }

  fclose(file);
}

float calculateBMI(float height, float weight) {
  return (weight * 10000) / (height * height);
}

int calorieIntake(float bmi) {
  if (bmi < 18.5) {
    return 2000;
  } else if (bmi >= 18.5 && bmi < 25) {
    return 2500;
  } else if (bmi >= 25 && bmi < 30) {
    return 2000;
  } else {
    return 1500;
  }
}

void createuser(char *name) {
  userdata newuser;
  strcpy(newuser.name, name);
  printf("Enter height and weight of the new user\n ");
  scanf("%f%f", &newuser.height, &newuser.weight);
  checkname[count++] = newuser;
    printUserDataFromFile(name);
}
int isNameInFile(char *name) {
  FILE *file = fopen("userdata.txt", "r");

  if (file == NULL) {
    printf("Error opening the file.\n");
    return -1;
  }

  userdata user;

  while (fscanf(file, "%s %f %f", user.name, &user.height, &user.weight) !=
         EOF) {
    if (strcmp(user.name, name) == 0) {
      fclose(file);
      return 1;
    }
  }

  fclose(file);
  return 0;
}

void printUserDataFromFile(char *name) {
  FILE *file = fopen("userdata.txt", "r");

  if (file == NULL) {
    printf("Error opening the file.\n");
    return;
  }

  userdata user;

  while (fscanf(file, "%s %f %f", user.name, &user.height, &user.weight) !=
         EOF) {
    printf("User Information:\n");
    printf("Height: %.2f\n", user.height);
    printf("Weight: %.2f\n", user.weight);
    printf("-------------------\n");
  }

  float bmi = calculateBMI(user.height, user.weight);
  printf("BMI: %.2f\n", bmi);

  int calorieIntakeValue = calorieIntake(bmi);
  printf("Calorie Intake Per Day: %d\n", calorieIntakeValue);

  fclose(file);
}

void addFoodItem(char foodName[50]) {
    FILE *file = fopen("calorieTable.txt", "r");
    if (file != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), file)) {
            char tempName[50];
            float tempCalories;
            sscanf(line, "%s %f", tempName, &tempCalories);
            if (strcmp(tempName, foodName) == 0) {
                printf("The calorie value of %s is %.2f.\n", foodName, tempCalories);
                fclose(file);
                return;
            }
        }
        fclose(file);
    }

    printf("Enter the calorie value of %s: ", foodName);
    float foodCalories;
    scanf("%f", &foodCalories);

    file = fopen("calorieTable.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(file, "%s %f\n", foodName, foodCalories);
    addFoodItems(foodName, foodCalories);
    fclose(file);
}

void menu() {
  printf("\n\n*** MEALS MENU ***\n");
  printf("1. Breakfast\n");
  printf("2. Lunch\n");
  printf("3. Dinner\n");
  printf("4. Exit\n");
  printf("Enter your choice");
  int choice = 0;
  scanf("%d", &choice);

  while (1) {
    switch (choice) {
    case 1:
      breakfast();
      break;
    case 2:
      lunch();
      break;
    case 3:
      dinner();
      break;
    case 4:
      mainMenu();
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }
}

void breakfast() {
    char foodName[50];
    printf("Enter the name of the breakfast food item: ");
    scanf(" %s", foodName);
    addFoodItem(foodName);
    menu();
}

void lunch() {
    char foodName[50];
    printf("Enter the name of the lunch food item: ");
    scanf("%s", foodName);
    if(strcmp(foodName, "e") == 1){
      exit(0);
    }
    addFoodItem(foodName);
    menu();
}

void dinner() {
    char foodName[50];
    printf("Enter the name of the dinner food item: ");
    scanf("%s", foodName);
    addFoodItem(foodName);
    menu();
}

float calculateCalories(char exercise[] ) {
    float distj;
    float times;
    float timec;
    float distr;
    float caloriesburnt;


    if (strcmp(exercise, "running") == 0) {
        printf("Enter disttance covered by Running:\n");
        scanf("%f",&distr); 
        caloriesburnt=distr*60;

    } else if (strcmp(exercise, "jogging") == 0) {
       printf("Enter distance covered by Jogging: \n");
       scanf("%f",&distj);
       caloriesburnt=distj*43;
    } else if (strcmp(exercise, "skipping") == 0) {
        printf("Enter the time you spent Skipping in min:\n");
        scanf("%f",&times);
        caloriesburnt=times*10;
    } else if (strcmp(exercise, "cycling") == 0) {
        printf("Enter the time you spent cycling in min: ");
        scanf("%f",&timec) ;
        caloriesburnt=timec*3;
    } else {
        printf("Exercise type not recognized.\n");
        return 0.0;
    }


    totalExercises += caloriesburnt;
    return caloriesburnt;
}

void exerciseMenu() {
  int choice;
  char exerciseType[20];
  float duration;
  
 while(1) {
      printf("\n\n*** MEALS MENU ***\n");
      printf("1. Running\n");
      printf("2. Jogging\n");
      printf("3. Skipping\n");
      printf("4. Cycling\n");
      printf("5. Exit\n");
      printf("Enter your choice: ");
      scanf("%d", &choice);

      switch(choice) {
          case 1:
              strcpy(exerciseType, "running");
              break;
          case 2:
              strcpy(exerciseType, "jogging");
              break;
          case 3:
              strcpy(exerciseType, "skipping");
              break;
          case 4:
              strcpy(exerciseType, "cycling");
              break;
          case 5:
              mainMenu();
          default:
              printf("Invalid choice. Please choose again.\n");
      }

      float caloriesBurned = calculateCalories(exerciseType) ;
      printf("Calories burned: %.2f\n", caloriesBurned);
   
    totalExercises++;
  } 
}

void calorieMenu() {
    int choice;
    float newIntake;

    printf("\n\n*** CALORIE MENU ***\n");
    printf("1. Calorie Intake\n");
    printf("2. Calorie Burn\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    float c = 0;
    float d = 0;
    scanf("%d", &choice);

  switch(choice){
      case 1:
        c = calculateTotalCaloriesIntake();
        printf("%.2f", c);
        break;
      case 2:
        d = totalExercises;
        printf("%.2f", d);
        break;
      case 3:
        mainMenu();
        break;
      default:
        printf("Invalid choice. Please choose again.\n");
        break;
  }
}
void mainMenu(){
  int choice = 0;

  while(1){
    printf("\n\n*** MAIN MENU ***\n");
    printf("1. Meals Menu\n");
    printf("2. Exercise Menu\n");
    printf("3. Calories Menu\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");

    scanf("%d", &choice);

    switch(choice){
      case 1:
        menu();
      break;
      case 2:
        exerciseMenu();
      break;
      case 3:
        calorieMenu();
      break;
      case 4:
        exit(0);
      default:
      printf("Invalid choice. Please choose again.\n");
    }
  }
}

int main(){

 char name[50];
 printf("Enter name");
 scanf("%s", name);
 int index = isNameInFile(name);
 if (index == 1) {
    printf("Welcome back!!");
    printUserDataFromFile(name);

 } else {
    printf("Creating new user\n");
    createuser(name);
 }
 save();
 mainMenu();
 return 0;
}