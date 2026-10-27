

//#include <math.h>
#include <limits.h>

#include <SDL\SDL.h>
#include <gl\gl.h>

//#include <plib\pw.h>
#include <plib\ul.h>        // general utils (basic for plib)
#include <plib\sg.h>        // vec maths
#include <plib\ssg.h>       // scene graph
#include <plib\ssgaux.h>    // extended primitives (teapot,sky,etc..)

#include "moto.h"

bool salir=false;
ssgRoot *raiz;
sgCoord campos;
moto *player1;
ssgTransform *bola;
ssgTransform *terreno;


Uint8 *keystate;
SDL_Joystick *joy;

void MovePlayer() {
    Sint16 axisX=(SDL_JoystickGetAxis(joy, 0));
    int vaxisY=(SDL_JoystickGetAxis(joy, 2));
    unsigned int axisY=-vaxisY-SHRT_MIN;

    {player1->setH(player1->getH()-((axisX/10000)*((float)axisY/(2*SHRT_MAX))));}
    {player1->setR((axisX*45/32000));}
    player1->Avanzar(axisY/10000);

    if (keystate[SDLK_UP]) player1->Avanzar();
    if (keystate[SDLK_DOWN]) player1->Retroceder();
    if (keystate[SDLK_RIGHT]) player1->setH(player1->getH()-2);
    if (keystate[SDLK_LEFT]) player1->setH(player1->getH()+2);
    if (keystate[SDLK_SPACE]) {player1->setXYZ(0,0,0);player1->setHPR(0,0,0);}
if (keystate[SDLK_p]) {player1->setP(15);}

    //mover al player sobre el terreno
    ssgHit *results;//resultados de colisiones
    sgMat4 ident;//matriz identidad...
    sgMakeIdentMat4(ident);
    sgCoord motocoord; //coordenadas de la moto
    sgVec3 pos; // posicion de busqueda
    sgVec3 posresult; //posicion resultado
    sgCoord tt; //coordenadas finales

    sgCopyCoord(&motocoord,&player1->getTrans()); //traigo las coord.moto para trab.mas comodo
    sgCopyVec3(pos,motocoord.xyz); //cojo solo la posicion
    pos[2]+=500;    // busco por encima de la pos.actual (para pendientes elevadas)

    //buscar colision "solo con el terreno"
    int v=ssgHOT(terreno,pos,ident,&results);

    if (v>0) { //ha habido colision "menos mal" uff :/
            ssgHit *h=&(results[0]);//colision 1... unica, se espera (plano al que corta)
            sgIsectInfLinePlane(posresult,pos,(sgVec3){0,0,-1},h->plane); //punto en el que corta
            sgSetCoord(&tt,posresult,motocoord.hpr);//componer coordenadas final (en la posicion, manteniendo orientacion moto)
            (player1->getTransform())->setTransform(&tt); //mover la moto a esas coordenadas

        //orientar la moto, segun inclinacion del terreno
/*
        sgVec3 orientresult;

        sgVec3 normal;
        sgSetVec3(normal,h->plane[0],h->plane[1],h->plane[2]);
        sgVec3 frente;
        sgSetVec3(frente,0,1,0);
        sgMat4 trans;
        player1->getTransform()->getTransform(trans);
        sgXformVec3(frente,trans);
        sgNormalizeVec3(frente);
        sgNormalizeVec3(normal);
        float angulo=sgScalarProductVec3(frente,normal);

        sgCopyVec3(orientresult,motocoord.hpr);
        angulo*=SG_RADIANS_TO_DEGREES;

        if (angulo<0) orientresult[1]=10; else orientresult[1]=-10;


        sgSetCoord(&tt,posresult,orientresult);
        (player1->getTransform())->setTransform(&tt);
*/
    } else { //si no se encuentra el suelo
        motocoord.xyz[2]=0; //poner la altura a cero (mantener el resto)
        (player1->getTransform())->setTransform(&motocoord); //mover la moto a esas coordenadas
    }


}

void Draw();

int main ( int argc, char** argv ) {
    //sdl windowing
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(640,480,16,SDL_OPENGL); // SDL_FULLSCREEN
    keystate=SDL_GetKeyState(NULL); //get keyboard-status (on PumpEvents)

    // basic openGL setup
    glEnable(GL_DEPTH_TEST);
    glClearColor(0,0,1,0);
    //if (!ulFileExists("moto.3ds")) {
    //    glClearColor(1,0,0,0);
    //};

    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    // Check for joystick     // Open joystick
    if (SDL_NumJoysticks()>0) joy=SDL_JoystickOpen(0);

    // init SSG
    ssgInit();
    ssgModelPath("./media");
    ssgTexturePath("./media");

    // SSG initiation (context)
    ssgSetFOV(45,0);
    ssgSetNearFar(2,10000);
    campos = (sgCoord){{0,-500,500},{0,-45,0}};
    ssgSetCamera(&campos);

    // SSG lights (8x openGL)
    for (int i=0;i<8;i++) {
        ssgGetLight(i)->off();
    }
    ssgLight *l=ssgGetLight(1);
    l->on();
    l->setColour(GL_AMBIENT,0,0,0);
    l->setColour(GL_DIFFUSE,1,1,1);
    l->setColour(GL_SPECULAR,0,0,0);
    l->setHeadlight(0);
    l->setPosition(20,-20,20);

    // SSG scene-tree
    raiz = new ssgRoot();

    player1 = new moto("moto_prb.3ds");
    player1->setVelocidad((sgVec3){0,5,0});
    raiz->addKid(player1->getTransform());

    ssgEntity *terrenoMesh = ssgLoad3ds("terreno.3ds",NULL);

    terreno=new ssgTransform();
    terreno->addKid(terrenoMesh);
    raiz->addKid(terreno);
    terreno->setName("terreno");

    ssgaSphere *bolaMesh=new ssgaSphere(120);
    bolaMesh->setSize(20);
    bola=new ssgTransform();
    bola->addKid(bolaMesh);
    raiz->addKid(bola);

    //raiz->print(stdout,"->",2);

    while(!salir) {
        SDL_PumpEvents(); // discard events & update keystate
        SDL_JoystickUpdate();  // update joysticks status
        MovePlayer();
        if (keystate[SDLK_ESCAPE]) salir=true;
        Draw();
    }

    //close joystick subsystem
      if(SDL_JoystickOpened(0))
        SDL_JoystickClose(joy);
    // close the window
    SDL_Quit();

    return 0;
}

void Draw() {
    // girar la camara... looking at moto
    sgVec3 lookat,lookhpr;
    sgSubVec3(lookat,(player1->getTrans()).xyz,campos.xyz);
    sgHPRfromVec3(lookhpr,lookat);
    lookhpr[1]*=(-1);
    sgCopyVec3(campos.hpr,lookhpr);
    ssgSetCamera(&campos);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ssgCullAndDraw(raiz);
    SDL_GL_SwapBuffers();
}
