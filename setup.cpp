#include "setup.h"


setUp::setUp()
{
    createRooms() ;
}


void setUp::createRooms() {

    Room *a, *b, *c, *d, *e, *f, *g, *h, *i,*j,*k,*l,*m,*n,*o,*p,*q, *r,*s,*t,*u,*w,*x;

       a = new Room("Medical Ward");
       b = new Room("Medical Hallway");
       c = new Room("Cold Room");
       d = new Room("Armoury");
       e = new Room("East Wing Lower");
       f = new Room("East Wing Middle");
       g = new Room("East Wing Upper");
       h = new Room("Control Room");
       i = new Room("Bio Lab");
       j = new Room("Weapons Depot");
       k = new Room("Research Room");
       l = new Room("Restroom");
       m = new Room("Storage Room");
       n = new Room("Storage Hallway");
       o = new Room("Decontamination Room");
       p = new Room("Minor Hallway");
       q = new Room("Laser Room");
       r = new Room("Exit Hallway Near");
       s = new Room("Exit Hallway Far");
       t = new Room("Elevator Room");
       u = new Room("Exit");
       w = new Room("Stairways");
       x = new Room("Reactor Room");

       Character *zombie1, *zombie2, *zombie3, *zombie4,*zombie5, *zombie6, *zombie7, *zombie8, *zombie9,*recon1, *recon2, *recon3, *recon4  ;

       //Item(1 Description, 2 Weight, 3 Value, 4 isEdible, 5 isWeapon, 6 HP_RestoreValue, 7 AttackDamValue)
       //Character(1 Description, 2 isEnemy, 3 AttackStrength, 4 HP)

       recon1 = new Character("Recon Corps", 0, 10, 70) ;
           Item *knife = new Item("Knife", 2, 20, 1, 0, 0, 10) ;
           recon1->addItem(knife);
           recon1->addItem(new Item("Bandages", 2, false, 0, 1, 30, 0));
           recon1->setEquipedWeapon(knife);

       recon2 = new Character("Recon Corps", 0, 5, 90) ;
           Item *gun = new Item("Handgun", 5, 0,1,0,0,20) ;
           recon2->addItem(new Item("Antibiotics",3,0,0,1,100,0)) ;
           recon2->addItem(gun) ;
           recon2->setEquipedWeapon(gun);

       recon3 = new Character("Recon Corps", 0, 10, 100) ;
           Item *machineGun = new Item("Machine Gun", 8, 0,1,0,0,30) ;
           recon3->addItem(new Item("Bandages", 2, 0,0,1,30,0)) ;
           recon3->addItem(new Item("Bandages", 2, 0,0,1,30,0)) ;
           recon3->addItem(machineGun) ;
           recon3->setEquipedWeapon(machineGun);

       recon4 = new Character("Recon Corps", 0, 10, 140) ;
            Item *machineGun2 = new Item("Machine Gun", 8, 0,1,0,0,30) ;
            recon3->addItem(new Item("Bandages", 2, 0,0,1,30,0)) ;
            recon3->addItem(machineGun2) ;
            recon3->setEquipedWeapon(machineGun2);

       zombie1 = new Character("Zombie",0,10,40) ;
       zombie2 = new Character("Zombie",0,10,50) ;
            zombie2->addItem(new Item("Baked Beans", 2, 0,0,1,30,0)) ;
       zombie3 = new Character("Zombie",0,20,60) ;
            zombie3->addItem(new Item("Peaches",3,0,0,1,40,0)) ;
       zombie4 = new Character("Zombie",0,10,70) ;
            Item *baseballBat = new Item("Baseball Bat",4 ,0,1,0,0,15) ;
            zombie4->addItem(baseballBat);
            zombie4->setEquipedWeapon(baseballBat);
            zombie4->addItem(new Item("Peaches",3,0,0,1,40,0));
       zombie5 = new Character("Zombie",0,25,90) ;
                 Item *knife2 = new Item("Knife",1 ,0,1,0,0,7) ;
                 zombie5->addItem(knife2);
                 zombie5->setEquipedWeapon(knife2);
                 zombie5->addItem(new Item("Baked Beans",2,0,0,1,20,0));
       zombie6 = new Character("Zombie",0,20,90) ;
                 Item *baseballBat2 = new Item("Baseball Bat",5 ,0,1,0,0,20) ;
                 zombie6->addItem(baseballBat2);
                 zombie6->setEquipedWeapon(baseballBat2);
                 zombie6->addItem(new Item("Peaches",3,0,0,1,35,0));
       zombie7 = new Character("Zombie",0,30,100) ;
                 zombie7->addItem(new Item("Antibiotics",2,0,0,1,80,0));
       zombie8 = new Character("Zombie",0,30,100) ;
       zombie9 = new Character("Zombie",0,10,180) ;


           a->addItem(new Item("Bandages", 2, 0,0,1,40,0));
           a->addItem(new Item("Knife", 2, 0,1,0,0,10));
           a->addItem(new Item("Baked Beans", 4, 0,0,1,35,0));
           a->addItem(new Item("Chart", 0, false,1,1,0,0)) ;

           b->addItem(new Item("Diary Entry", 0, false,1,1,0,0)) ;

           c->addItem(new Item("Journal 1", 0, false,1,1,0,0)) ;
                c->addItem(new Item("Antibiotics",3 , 0,0,1,70,0)) ;

           d->addItem(new Item("Journal 2", 0, false,1,1,0,0)) ;
                d->addItem(new Item("Bandages", 2, 0,0,1,30,0));

           e->addItem(new Item("Journal 3", 0, false,1,1,0,0)) ;
                e->addCharacter(zombie1);
                e->addCharacter(zombie2);

           f->addItem(new Item("Journal 4", 0, false,1,1,0,0)) ;
           f->addItem(new Item("Antibiotics",3,0,0,1,100,0));

           g->addItem(new Item("Journal 5", 0, false,1,1,0,0)) ;           
                g->addCharacter(zombie4);

           h->addItem(new Item("Journal 6", 0, false,1,1,0,0)) ;
                h->addItem(new Item("Baked Beans", 4, 0,0,1,30,0));
           i->addItem(new Item("Journal 7", 0, false,1,1,0,0)) ;

           j->addItem(new Item("Baseball Bat", 3, 0,1,0,0,12));
           j->addItem(new Item("Journal 8", 0, false,1,1,0,0)) ;
                j->addCharacter(zombie3);

           k->addItem(new Item("Journal 9", 0, false,1,1,0,0)) ;

           l->addItem(new Item("Journal 10", 0, false,1,1,0,0)) ;
           //l->addItem(new Item("Antibiotics",3 , 0,0,1,100,0));
           n->addCharacter(zombie8);
                n->addItem(new Item("Baked Beans",2 , 0,0,1,40,0)) ;

           m->addItem(new Item("Journal 11", 0, false,1,1,0,0)) ;

           o->addItem(new Item("Journal 12", 0, false,1,1,0,0)) ;
           o->addItem(new Item("Peaches", 4, 0,0,1,30,0)) ;
                o->addCharacter(recon1);

           p->addItem(new Item("Bandages", 2, 0,0,1,10,0));
           p->addItem(new Item("Bandages", 2, 0,0,1,10,0));
           p->addItem(new Item("Knife", 2, 0,1,0,0,8));

           p->addItem(new Item("Antibiotics",3 , 0,0,1,100,0));
           p->addItem(new Item("Journal 13", 0, false,1,1,0,0)) ;

           q->addItem(new Item("Journal 14", 0, false,1,1,0,0)) ;

           r->addItem(new Item("Bandages", 2, 0,0,1,10,0));

           s->addCharacter(recon2);
           s->addCharacter(zombie5);

           w->addCharacter(recon3);
           w->addCharacter(zombie7);
                w->addItem(new Item("Peaches",2 , 0,0,1,40,0));

           x->addCharacter(recon4);
           x->addCharacter(zombie6);
           x->addCharacter(zombie9);

            a->setExits(b, NULL,NULL,NULL,NULL,NULL);
            b->setExits(NULL,c, NULL, i,NULL,NULL);
            c->setExits(NULL,d,NULL, b,NULL,NULL);
            d->setExits(e, NULL, NULL, c,NULL,NULL);
            e->setExits(f, NULL, d, NULL,NULL,NULL);
            f->setExits(g, NULL, e, p,NULL,NULL);
            g->setExits(h, NULL, f, NULL,NULL,NULL);
            h->setExits(NULL, NULL, g,NULL,NULL,NULL);
            i->setExits(NULL, b,NULL,j,NULL,NULL);
            j->setExits(k,i, NULL, NULL,NULL,NULL);
            k->setExits(m,NULL,j, l,NULL,NULL);
            l->setExits(NULL, k, NULL, NULL,NULL,NULL);
            m->setExits(NULL, n, k, NULL,NULL,NULL);
            n->setExits(NULL, o, NULL, m,NULL,NULL);
            o->setExits(q ,p, NULL, n,NULL,NULL);
            p->setExits(NULL, f, NULL,o,NULL,NULL);
            q->setExits(r, NULL, o, NULL,NULL,NULL);
            r->setExits(NULL, NULL, q, s,NULL,NULL);
            s->setExits(t, r, NULL,NULL,NULL,NULL);
            t->setExits(u,NULL,s,w,NULL,NULL);
            u->setExits(NULL,NULL, t, NULL,NULL,NULL);
            w->setExits(NULL, t, NULL, x,NULL,NULL);
            x->setExits(NULL, w, NULL, NULL,NULL,NULL);

    currentRoom = a;
}

Room* setUp::getCurrentRoom() {

    return currentRoom ;

}
