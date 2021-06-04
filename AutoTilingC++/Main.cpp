#include "raylib.h"
#include <iostream>
#include <stdio.h>  
#include <math.h> 
#include <vector>
#include "Tile.h"
#include "Player.h"
#include "Utility.h"
#include "Projectile.h"

using namespace std;

void Uptade();
void Draw();
void Start();


//Setup la taille de l'écran
int const screenWidth = 800;
int const screenHeight = 450;

//Setup la taille des cellules
const int CellWidth = 32;
const int CellHeight = 32;

//Setup la taille que la grilla va avoir
const int  GridWidth = screenWidth / CellWidth;
const int GridHeight = screenHeight / CellHeight;

//Setup la grille dans laquelle on va stoques des objets de type tile
Tile* Grid[GridWidth][GridHeight];

Vector2 CalculatePositionInGrid(const Vector2& pos);

//Setup le fait qu'il va y avoir une texture(un sprite) utilisé par les tiles
Texture2D texture;
Texture2D playerTexture;


//Setup le player
Player player;
vector <Projectile*> projectile;


int main(int argc, char* argv[])
{
    //Fill la grille Grid de valeur 0
    memset(Grid, 0, sizeof(Tile*) * GridWidth * GridHeight);

    //Créer un écran et on met les fps à 60
    InitWindow(screenWidth, screenHeight, "AutoTilingC++");
    SetTargetFPS(60);

    //Charge la texture
   // texture = LoadTexture("H:/Cretion Jeu/C++/AutoTiling/_AutoTilingC++/resources/TileMapTest3.png");
    texture = LoadTexture("H:/Cretion Jeu/C++/AutoTiling/_AutoTilingC++/resources/TileMapV1.png");
    playerTexture = LoadTexture("H:/Cretion Jeu/C++/AutoTiling/_AutoTilingC++/resources/PlayerV1.png");

    Start();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        Uptade();
        // Draw
        Draw();

    }
    CloseWindow();

    return 0;


}

Vector2 CalculatePositionInGrid(const Vector2& pos)
{
    // cout << "Position de la souris: " << mousePos.x << " : " << mousePos.y << endl;
    float mouseInGridX = floor(pos.x / CellWidth);
    float mouseInGridY = floor(pos.y / CellHeight);

    Vector2 posInGrid = Vector2{ mouseInGridX,mouseInGridY };

    return posInGrid;

}

Vector2 CalculatePositionInGrid(const int x, const int y)
{
    // cout << "Position de la souris: " << mousePos.x << " : " << mousePos.y << endl;
    float InGridX = floor(x / CellWidth);
    float InGridY = floor(y / CellHeight);

    Vector2 posInGrid = Vector2{ InGridX,InGridY };

    return posInGrid;

}


int  Conversion(int arg)
{
    //Converti la valeur données pour resortir une valeur comprise entre 1 et 47
    switch (arg)
    {
        case 0:		return 47; break;
        case 2:		return 1; break;
        case 8:		return 2; break;
        case 10:	return 3; break;
        case 11:	return 4; break;
        case 16:	return 5; break;
        case 18:	return 6; break;
        case 22:	return 7; break;
        case 24:	return 8; break;
        case 26:	return 9; break;
        case 27:	return 10; break;
        case 30:	return 11; break;
        case 31:	return 12; break;
        case 64:	return 13; break;
        case 66:	return 14; break;
        case 72:	return 15; break;
        case 74:	return 16; break;
        case 75:	return 17; break;
        case 80:	return 18; break;
        case 82:	return 19; break;
        case 86:	return 20; break;
        case 88:	return 21; break;
        case 90:	return 22; break;
        case 91:	return 23; break;
        case 94:	return 24; break;
        case 95:	return 25; break;
        case 104:	return 26; break;
        case 106:	return 27; break;
        case 107:	return 28; break;
        case 120:	return 29; break;
        case 122:	return 30; break;
        case 123:	return 31; break;
        case 126:	return 32; break;
        case 127:	return 33; break;
        case 208:	return 34; break;
        case 210:	return 35; break;
        case 214:	return 36; break;
        case 216:	return 37; break;
        case 218:	return 38; break;
        case 219:	return 39; break;
        case 222:	return 40; break;
        case 223:	return 41; break;
        case 248:	return 42; break;
        case 250:	return 43; break;
        case 251:	return 44; break;
        case 254:	return 45; break;
        case 255:	return 46; break;
        default: return arg;
    }

}

int CheckTiles(Vector2 tilePos)
{
    //On va check si autour de la position données il y a d'autres tiles
    #pragma region CheckTiles

    int posX = tilePos.x; // Position en X de la tile
    int posY = tilePos.y; // Position en Y de la tile

    int North = tilePos.y - 1; // La position au nord de la tile
    int South = tilePos.y + 1; // La position au sud de la tile

    int East = tilePos.x + 1; // La position à l'est de la tile
    int West = tilePos.x - 1; // La position à l'ouest de la tle

    int value = 0; // Setup la value qui va nous permettre de savoir à la fin ce qui entour la tile

    //Haut
    if (Grid[West][North] != 0) //Si la case du tableau en haut à gauche n'est pas vide
    {
        if ((Grid[posX][North] != 0)&&(Grid[West][posY]!=0))
        {
            value += 1 * 1;
        }
    }
    if (Grid[posX][North] != 0) //Si la case du tableau en haut n'est pas vide
    {
        value += 2 * 1;
    }
    if (Grid[East][North] != 0)//Si la case du tableau en haut à droite n'est pas vide
    {
        if ((Grid[posX][North] != 0) && (Grid[East][posY] != 0))
        {
            value += 4 * 1;
        }  
    }

    //Bas
    if (Grid[West][South] != 0) //Si la case du tableau en bas à gauche n'est pas vide
    {
        if ((Grid[posX][South] != 0) && (Grid[West][posY] != 0))
        {
            value += 32 * 1;
        }
    }
    if (Grid[posX][South] != 0) //Si la case du tableau en bas n'est pas vide
    {
        value += 64 * 1;
    }
    if (Grid[East][South] != 0) //Si la case du tableau en bas à droite n'est pas vide
    {
        if ((Grid[posX][South] != 0) && (Grid[East][posY] != 0))
        {
            value += 128 * 1;
        }
    }

    //Gauche
    if (Grid[West][posY] != 0) //Si la case du tableau à gauche n'est pas vide
    {
        value += 8 * 1;
    }

    //Droit
    if (Grid[East][posY] != 0) //Si la case du tableau à droite n'est pas vide
    {
        value += 16 * 1;

    }

    value = Conversion(value); //Convertie la valeur pour en sorte que ça aille de 1 à 47

    return value;
    #pragma endregion
}


void ChangesTiles()
{
    //Regarder dans toutes les cases du tableau(de la grille)
    for (int width = 0; width < GridWidth; width++)
    {
        for (int height = 0; height < GridHeight; height++)
        {
            if (Grid[width][height] != NULL) //Si il y a quelque chose dans le case
            {
                // cout << "Valeur de = " << width << " : " << height << " autour =  " << CheckTiles(Grid[width][height]->position) << endl<< endl;
                Vector2 position = {Grid[width][height]->x,Grid[width][height]->y}; //Faire un vector 2 de la position de la tuile 
                Grid[width][height]->ChangeSprite(CheckTiles(position)); //On appel la fonction de changement de sprite de la tuile et on lui donne la value recup dans checkTile
                //Vector2 pos = Grid[width][height]->position;
            }
        }
    }

}

void PlaceTile(Vector2 position)
{
    int x = position.x;
    int y = position.y;
    Grid[x][y] = new Tile(x, y, CellWidth, texture); // Créer une tile à la position x,y de size de taille de cellule, et de sprite la texture
    //cout << "Position = " << position.x << " : " << position.y << endl << endl;
    ChangesTiles(); //Appel la fonction qui va changer les tiles de toutes les tiles

}

void RemoveTile(Vector2 position)
{
    int x = position.x;
    int y = position.y;
    Grid[x][y] = 0; //Reset la value du tableau à l'emplacement x,y
    std::cout << "TIle removed "<<x <<" :"  << y<< endl;
    ChangesTiles();
}

void FillGrid()
{
    for (int width = 0; width < GridWidth; width++)
    {
        for (int height = 0; height < GridHeight; height++)
        {
            Grid[width][height] = new Tile(width, height, CellWidth, texture);
        }
    }
    ChangesTiles();

}

Vector2 ChangeDirection(Vector2 positionInit)
{
    int direction = rand() % 4;
    //Faut check si dans deux dans la direction tu refait un random
    // 
    //cout << "Direction: " << direction << endl;
    Vector2 posInitiale = positionInit;
    if (direction == 0)
    {
        positionInit.x += 1;
    }
    else if (direction == 1)
    {
        positionInit.x -= 1;
    }
    else if (direction == 2)
    {
        positionInit.y += 1;
    }
    else if (direction == 3)
    {
        positionInit.y -= 1;
    }
    //cout << "Position Initiale : " << positionInit.x << " : " << positionInit.y << endl;
    

    if ((positionInit.x-1 < 0) || (positionInit.x+2 > GridWidth) || (positionInit.y-1 < 0) || (positionInit.y+2 > GridHeight))
    {
        ChangeDirection(posInitiale);
    }
    else
    {
        return positionInit;
    }


}

int sizeToRemove = 800; // Combien de tiles on enlève
void RemoverMove()
{
    //Setup la position de départ
    int xRandom = rand() % GridWidth;
    int yRandom = rand() % GridHeight;
    //cout << "X : " << xRandom << "Y: " << yRandom << endl;

    Vector2 position = {xRandom,yRandom};
    

    for (int i = 0; i < sizeToRemove;i++)
    {
        position = ChangeDirection(position);
        //Choisit une direction entre nord sud east west

        int x = position.x;
        int y = position.y;
        
        if (Grid[x][y] != NULL)
        {
            RemoveTile(position);
        }


        //cout << "Actual Position : " << position.x << " : " << position.y << endl;
        
        if ((x <0) || (x > GridWidth) || (y < 0) || (y > GridHeight))
        {
            std::cout << "Prochaine case vide" << endl;
        }
        else
        {
            
        }


    }
    //Remove la tile dans la direction

    

}


static int AABBCollision(const Rectangle& rectA)
{
    Vector2 playerDirection = player.GetDirection();

    int xMinA = rectA.x;
    int xMaxA = rectA.x + rectA.width-1;
    int yMinA = rectA.y;
    int yMaxA = rectA.y + rectA.height-1;


    Vector2 HautGauche = CalculatePositionInGrid(xMinA,yMinA);
    Vector2 HautDroit = CalculatePositionInGrid(xMaxA, yMinA);
    Vector2 BasDroit = CalculatePositionInGrid(xMaxA, yMaxA);
    Vector2 BasGauche = CalculatePositionInGrid(xMinA, yMaxA);

    bool HitHautGauche = Grid[(int)HautGauche.x][(int)HautGauche.y] != 0;
    bool HitHautDroit = Grid[(int)HautDroit.x][(int)HautDroit.y] != 0;
    bool HitBasDroit = Grid[(int)BasDroit.x][(int)BasDroit.y] != 0;
    bool HitBasGauche = Grid[(int)BasGauche.x][(int)BasGauche.y] != 0;

    DrawCircle(xMinA, yMinA, 1, WHITE);
    DrawCircle(xMinA, yMaxA, 1, WHITE);
    DrawCircle(xMaxA, yMaxA, 1, WHITE);
    DrawCircle(xMaxA, yMinA, 1, WHITE);

    int value = HitNo;
    if (HitHautGauche)
    {
        if (HitBasGauche)
        {
            value |= HitGauche;
        }
        if (HitHautDroit)
        {
            value |= HitHaut;
        }

        if (!HitBasGauche && !HitHautDroit)
        {
            if (playerDirection.x < 0)
            {
                value |= HitGauche;
            }
            if (playerDirection.y < 0)
            {
                value |= HitHaut;
            }
            
        }


    }
    
    if (HitHautDroit)
    {
        if (HitBasDroit)
        {
            value |= HitDroit;
        }
        if (HitHautGauche)
        {
            value |= HitHaut;
        }
        if (!HitBasDroit && !HitHautGauche)
        {
            if (playerDirection.x > 0)
            {
                value |= HitDroit;
            }
            if (playerDirection.y < 0)
            {
                value |= HitHaut;
            }
            
           
        }


    }
    
    if (HitBasGauche)
    {
        if (HitHautGauche)
        {
            value |= HitGauche;
        }
        if (HitBasDroit)
        {
            value |= HitBas;
        }
        if (!HitHautGauche && !HitBasDroit)
        {
            if (playerDirection.x < 0)
            {
                value |= HitGauche;
            }
            if (playerDirection.y > 0)
            {
                value |= HitBas;
            }
            
            
        }

    } 
    if (HitBasDroit)
    {
        if (HitHautDroit)
        {
            value |= HitDroit;
        }
        if (HitBasGauche)
        {
            value |= HitBas;
        }
        if (!HitHautDroit && !HitBasGauche)
        {
            if (playerDirection.x > 0)
            {
                value |= HitDroit;
            }
            if (playerDirection.y > 0)
            {
                value |= HitBas;
            }
            
            
        }


    }
 
    //std::cout << "Value: " << value << std::endl;
    return value;
    
}



void Collisions()
{
    player.Movement();
    //Collisions
    int horizontalDirection = player.GetDirection().x;
    int verticalDirection = player.GetDirection().y;

    Vector2 playerPos = { player.x,player.y };

    int posX = CalculatePositionInGrid(playerPos).x ; // Position en X de la tile
    int posY = CalculatePositionInGrid(playerPos).y; // Position en Y de la tile

    //Rectangle Anticipé
    Rectangle posAnticipePlayer = { playerPos.x + horizontalDirection, playerPos.y + verticalDirection,player.width,player.height };
    //DrawRectangle(posAnticipePlayer.x,posAnticipePlayer.y, posAnticipePlayer.width,posAnticipePlayer.height, BROWN);
    // DrawRectangleLines(posAnticipePlayer.x, posAnticipePlayer.y, posAnticipePlayer.width, posAnticipePlayer.height, BROWN);
    
    int colliding = 0;
    colliding = AABBCollision(posAnticipePlayer);
    player.Collisions(colliding);
   
}


void BulletCollisions()
{
    std::vector <Projectile*>::iterator itb = projectile.begin();
    while ( itb != projectile.end())
    {
        Rectangle recBullet = (*itb)->GetRect();
        int colliding = 0;
        colliding = AABBCollision(recBullet);
        int x = (*itb)->x;
        int y = (*itb)->y;
        if (colliding != 0)
        {
            Vector2 pos = CalculatePositionInGrid(x,y);
            //DrawRectangle(pos.x*32, pos.y*32, 32, 32, BROWN);
            //RemoveTile(pos);
            std::cout << "Pos : " << pos.x << " : " << pos.y << endl;
            
            delete(*itb);
            itb = projectile.erase(itb);
        }
        else
        {
            itb++;
        }
    }


    
   
}


void PlacePlayerStart()
{
    //Cherche un x en random
    //Cherche un y en random
    //Tant que Grid[x][y] != null chercher un x et un y différent
    int x = 0;
    int y = 0;
    
    while (Grid[x][y] != 0)
    {
        x = rand() % GridWidth;
        y = rand() % GridHeight;
        std::cout << "Pos : " << x << " : " << y << endl;
    }
    std::cout << "FinalPos : " << x << " : " << y << endl;
    Vector2 pos = CalculatePositionInGrid(x, y);
    float InGridX = floor(x / CellWidth);
    float InGridY = floor(y / CellHeight);
    std::cout << "Pos convertie: " << InGridX << " : " << InGridY << endl;
    player = Player(x*CellWidth, y*CellHeight, 32, 32,playerTexture);
    

}

void PlacePlayerEnd(Vector2 playerStart)
{


}

Vector2 CalculateAngle(Vector2 pos1, Vector2 pos2)
{
    Vector2 vecteur = { pos1.x-pos2.x, pos1.y-pos2.y};
    double vectorLength = sqrt( (vecteur.x * vecteur.x) + (vecteur.y * vecteur.y) );
    double normVectorX = vecteur.x/ vectorLength;
    double normVectorY = vecteur.y/ vectorLength;


    Vector2 direction = { normVectorX,normVectorY };

   return direction;

}

void Shoot(Vector2 direction)
{
    Vector2 size = { 16,16 };
    Vector2 mousePosition = GetMousePosition();
    Vector2 dir = CalculateAngle(mousePosition, { (float)(player.x + (player.width / 2)),(float)( player.y + (player.height / 2)) } );
    //Faut un vecteur entre la position du joueur et la position de la souris
    //Faut caluler le sinus/autre 
    projectile.push_back(new Projectile((float)player.x + (player.width / 2), (float)player.y + (player.height / 2), size, dir, 2));
    std::cout << "SHOOT" << endl;

}





void Start()
{
    //cout << "Grid Size : " << GridWidth << " : " << GridHeight << endl;
    FillGrid();
    RemoverMove();

    PlacePlayerStart();

}



void Uptade() 
{
    Vector2 mousePosition = GetMousePosition();
    Collisions();
    BulletCollisions();
    player.Update();
    //Plaçage de tile
    
    /*
    #pragma region Plaçage de tile
    if ((mousePosition.x > 0) && (mousePosition.x < screenWidth) && (mousePosition.y > 0) && (mousePosition.y < screenHeight))
    {
        //cout << "Mouse pos: " << mousePosition.x << " : " << mousePosition.y << endl;
        Vector2 mouseInGrid = CalculatePositionInGrid(mousePosition);
        //cout << "MouseX: " << CalculatePositionInGrid(mousePosition).x << endl << "MouseY: " << CalculatePositionInGrid(mousePosition).y << endl;
        int x = mouseInGrid.x;
        int y = mouseInGrid.y;

        //Place tile
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            if (Grid[x][y] == NULL) //Si on clique sur du vide(pas de tile)
            {
                PlaceTile(mouseInGrid);
            }

        }
        //Enlève tile
        else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
        {
            if (Grid[x][y] != NULL)
            {
                RemoveTile(mouseInGrid);
            }
        }

    }
    #pragma endregion
    */

    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouseDirection = GetMousePosition();

        Shoot(mouseDirection);
    }

    for (std::vector <Projectile*>::iterator itb = projectile.begin(); itb != projectile.end(); itb++)
    {
        (*itb)->Uptade();
    }

}

static int value = 0;
void Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    for (int width = 0; width < GridWidth; width++)
    {
        for (int height = 0; height < GridHeight; height++)
        {    
            if( Grid[width][height] != NULL)
            {
                Vector2 position = { Grid[width][height]->x,Grid[width][height]->y };
                value = CheckTiles(position);
                //DrawRectangleLines(width * CellWidth, height * CellHeight, CellWidth,CellWidth,RED );
                DrawText(TextFormat(" %4i", value), width * CellWidth, height * CellHeight, 8, RED);
                Grid[width][height]->Draw(); // Dessine chaque Tile de la grille
               
            }           
        }

    }

    for (std::vector <Projectile*>::iterator itb = projectile.begin(); itb != projectile.end(); itb++)
    {
        (*itb)->Draw();
    }
    player.Draw();

    EndDrawing();

}



