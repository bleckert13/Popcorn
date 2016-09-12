//
//  Constants.h
//  Popcorn
//
//  Created by Hans on 7/23/16.
//
//

#ifndef Constants_h
#define Constants_h

#define G_OWIDTH (1600.0f)
#define G_OHEIGHT (1200.0f)

#define G_SWIDTH    (Director::getInstance()->getVisibleSize().width)  //Screen width
#define G_SHEIGHT   (Director::getInstance()->getVisibleSize().height)   //Screen height

#define G_SCALEX    (G_SWIDTH / G_OWIDTH)
#define G_SCALEY    (G_SHEIGHT / G_OHEIGHT)
#define G_SCALEO    (G_SCALEX<G_SCALEY?G_SCALEX:G_SCALEY)
#define G_SCALEM    (G_SCALEX>G_SCALEY?G_SCALEX:G_SCALEY)

#define T_TUTOR_TITLE   "Tap to make Popcorn!"
#define T_TUTOR_DES     "Tap on the icons at the bottom to upgrade your popping abilities. Everything from increasing your kernels per click to unlockables. "
#define T_TUTOR_ITEM1   "Collect shakers by purchasing upgrades to unlock custom kernels"
#define T_TUTOR_ITEM2   "Prestige to unlock new backgrounds"

#define T_REVIEW_TITLE  "Love Kernel King?"
#define T_REVIEW_DESC   "Let the world know why you can't get enough of it."
#define T_REVIEW_SUGG   "Have a suggestion? We'd love to hear it!"
#define T_REVIEW_CANCEL "I don't love it"
#define T_REVIEW_RATE   "Rate Kernel King & Earn a Bonus"

#define T_VIDEO_TITLE   "Watch Video"
#define T_EMAIL_ADDRESS "kernelkingapp@gmail.com"
#endif /* Constants_h */
