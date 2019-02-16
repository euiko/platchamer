Frame BaseFrame;
#define BASE_FRAME BaseFrame
Xv_Window BasePanel;
Panel_item Button_Left;
Panel_item Button_Right;
Panel_item Button_Up;
Panel_item Button_Down;
Panel_item Button_Quit;
Panel_item Button_Fore;
Panel_item Button_Back;
Panel_item Button_Draw;

int Button_Left_Proc();
int Button_Right_Proc();
int Button_Up_Proc();
int Button_Down_Proc();
int Button_Quit_Proc();
int Button_Fore_Proc();
int Button_Back_Proc();
int Button_Draw_Proc();

static Server_image image_pr_1;

static unsigned short image_src_1[] = {
#include "up.ico"
};
static Server_image image_pr_2;

static unsigned short image_src_2[] = {
#include "down.ico"
};
static Server_image image_pr_3;

static unsigned short image_src_3[] = {
#include "left.ico"
};
static Server_image image_pr_4;

static unsigned short image_src_4[] = {
#include "right.ico"
};
int ok_to_notify=FALSE;

Xv_object auto_connect(item,event)
Xv_object item;
Event *event;
{
  Xv_object ret;

  ret = (Xv_object) -1;
  if(!ok_to_notify) return(ret);

  ret = (Xv_object) -2;

  return(ret);
}
