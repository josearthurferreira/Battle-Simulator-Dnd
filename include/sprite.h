#ifndef INCLUDE_SPRITE_H_
#define INCLUDE_SPRITE_H_

class Sprite {
public:
  Sprite();
  ~Sprite();
  void update(void);
  void render(void);

private:
  void *data;
};

#endif // INCLUDE_SPRITE_H_
