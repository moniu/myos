#include "keyboard.h"

#define loop(x,m) (x==m?0:x)
#define _KQS 64


struct keyboard_queue_t keyboard_queue;
struct keyboard_event_t keyboard_queue_events[_KQS];

struct
{
  uint8_t shift:1;
  uint8_t ctrl:1;
  uint8_t alt:1;
} keys_pressed;

void keyboard_setup()
{
  keyboard_queue.events = keyboard_queue_events;
  keyboard_queue.start = 0;
  keyboard_queue.end = 0;
  keyboard_queue.size = _KQS;
  keyboard_queue.full = 0;
}

void keyboard_push(struct keyboard_event_t event)
{
  if (keyboard_queue.start==keyboard_queue.end && keyboard_queue.full)
  {
    keyboard_queue.events[keyboard_queue.end] = event;
    keyboard_queue.start = loop(keyboard_queue.start+1,_KQS);
    keyboard_queue.end = keyboard_queue.start;
  }
  else
  {
    keyboard_queue.events[keyboard_queue.end] = event;
    keyboard_queue.end = loop(keyboard_queue.end+1,_KQS);
    if (keyboard_queue.end==keyboard_queue.start)
      keyboard_queue.full=1;
  }
}

struct keyboard_event_t keyboard_pop(void)
{
  
  if (keyboard_queue.end == keyboard_queue.start && keyboard_queue.full==0)
    return (struct keyboard_event_t ){0};
  else
  {
    struct keyboard_event_t returned_event;
    returned_event = keyboard_queue.events[keyboard_queue.start];
    keyboard_queue.start=loop(keyboard_queue.start+1,_KQS);
    keyboard_queue.full=0;
    return returned_event;
  }
  
}	

void keyboard_handler(struct regs* r)
{
    (void)r;
    uint8_t scancode;
    scancode = inportb(0x60);

    struct keyboard_event_t new_event;
    new_event.used = 1;
    new_event.keydown = scancode<0x80;
    new_event.key = scancode;
    keyboard_push(new_event);
}

void keyboard_queue_handler(void (handler)(char))
{   
  struct keyboard_event_t event;
  for(;;)
  {
    event = keyboard_pop();
    if (!event.used)
    {
      break;
    }
    if (event.keydown)
    {
      switch(event.key)
      {
        case 0x2A:
          keys_pressed.shift=1;
          break;
        case 0x1D:
          keys_pressed.ctrl=1;
          break;
        case 0x38:
          keys_pressed.alt=1;
          break;

        case 0x02:
          handler(keys_pressed.shift?'!':'1');
        break;
        case 0x03:
          handler(keys_pressed.shift?'@':'2');
        break;
        case 0x04:
          handler(keys_pressed.shift?'#':'3');
        break;
        case 0x05:
          handler(keys_pressed.shift?'$':'4');
        break;
        case 0x06:
          handler(keys_pressed.shift?'%':'5');
        break;
        case 0x07:
          handler(keys_pressed.shift?'^':'6');
        break;
        case 0x08:
          handler(keys_pressed.shift?'&':'7');
        break;
        case 0x09:
          handler(keys_pressed.shift?'*':'8');
        break;
        case 0x0A:
          handler(keys_pressed.shift?'(':'9');
        break;
        case 0x0B:
          handler(keys_pressed.shift?')':'0');
        break;
        case 0x0C:
          handler(keys_pressed.shift?'_':'-');
        break;
        case 0x0D:
          handler(keys_pressed.shift?'+':'=');
        break;
        case 0x0E:
          handler('\b');
        break;


        case 0x10:
          handler('q' - keys_pressed.shift*32);
        break;
        case 0x11:
          handler('w' - keys_pressed.shift*32);
        break;
        case 0x12:
          if (keys_pressed.alt)
            handler(keys_pressed.shift?129:137);
          else
            handler('e' - keys_pressed.shift*32);
        break;
        case 0x13:
          handler('r' - keys_pressed.shift*32);
        break;
        case 0x14:
          handler('t' - keys_pressed.shift*32);
        break;
        case 0x15:
          handler('y' - keys_pressed.shift*32);
        break;
        case 0x16:
          handler('u' - keys_pressed.shift*32);
        break;
        case 0x17:
          handler('i' - keys_pressed.shift*32);
        break;
        case 0x18:
          if (keys_pressed.alt)
            handler(keys_pressed.shift?131:139);
          else
            handler('o' - keys_pressed.shift*32);
        break;
        case 0x19:
          handler('p' - keys_pressed.shift*32);
        break;
        case 0x1A:
          handler(keys_pressed.shift?'{':'[');
        break;
        case 0x1B:
          handler(keys_pressed.shift?'}':']');
        break;
        case 0x1C:
          handler('\n');
        break;

        case 0x1E:
          if (keys_pressed.alt)
            handler(keys_pressed.shift?127:135);
          else
            handler('a' - keys_pressed.shift*32);
        break;
        case 0x1F:
          if (keys_pressed.alt)
            handler(keys_pressed.shift?132:140);
          else
            handler('s' - keys_pressed.shift*32);
        break;
        case 0x20:
          handler('d' - keys_pressed.shift*32);
        break;
        case 0x21:
          handler('f' - keys_pressed.shift*32);
        break;
        case 0x22:
          handler('g' - keys_pressed.shift*32);
        break;
        case 0x23:
          handler('h' - keys_pressed.shift*32);
        break;
        case 0x24:
          handler('j' - keys_pressed.shift*32);
        break;
        case 0x25:
          handler('k' - keys_pressed.shift*32);
        break;
        case 0x26:
          if (keys_pressed.alt)
            handler(keys_pressed.shift?143:144);
          else
            handler('l' - keys_pressed.shift*32);
        break;
        case 0x27:
          handler(';' - keys_pressed.shift);
        break;
        case 0x28:
          handler(keys_pressed.shift?'"':'\'');
        break;
        case 0x29:
          handler(keys_pressed.shift?'`':'~');
        break;
        case 0x2B:
          handler(keys_pressed.shift?'|':'\\');
        break;
        case 0x2C:
          if (keys_pressed.alt)
            handler(keys_pressed.shift?134:142);
          else
            handler('z' - keys_pressed.shift*32);
        break;
        case 0x2D:
          if (keys_pressed.alt)
            handler(keys_pressed.shift?133:141);
          else
            handler('x' - keys_pressed.shift*32);
        break;
        case 0x2E:
          if (keys_pressed.alt)
            handler(keys_pressed.shift?128:136);
          else
            handler('c' - keys_pressed.shift*32);
        break;
        case 0x2F:
          handler('v' - keys_pressed.shift*32);
        break;
        case 0x30:
          handler('b' - keys_pressed.shift*32);
        break;
        case 0x31:
          if (keys_pressed.alt)
            handler(keys_pressed.shift?130:138);
          else
            handler('n' - keys_pressed.shift*32);
        break;
        case 0x32:
          handler('m' - keys_pressed.shift*32);
        break;
        case 0x33:
          handler(keys_pressed.shift?'<':',');
        break;
        case 0x34:
          handler(keys_pressed.shift?'>':'.');
        break;
        case 0x35:
          handler(keys_pressed.shift?'?':'/');
        break;
        case 0x39:
          handler(' ');
        break;

        default:
          handler(219);
      }
    }
    else
    {
      switch(event.key)
      {
        case 0xAA:
          keys_pressed.shift=0;
          break;
        case 0x9D:
          keys_pressed.ctrl=0;
          break;
        case 0xB8:
          keys_pressed.alt=0;
          break;
      }
    }
  }
}

