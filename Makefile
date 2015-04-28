CMP = g++
MAIN = main
DOT_OS = AnimatedTexture.o Block.o Boomerang.o Bullet.o Camera.o ContentManager.o Enemy.o Fireball.o Geom.o Goomba.o Hammer.o HammerBro.o LayerController.o MapLayer.o ObjectLayer.o OneWayPlatform.o Player.o PlayerSpawn.o ProgressBar.o Projectile.o TestCollider.o Texture.o TileLayer.o Tileset.o TriggerArea.o WorldDebugger.o WorldMap.o WorldObject.o FireMagic.o FireWizard.o EnemyBoundary.o ScreenManager.o MenuScreen.o MainMenuScreen.o Screen.o
HEADERS = AnimatedTexture.h Animation.h Block.h Boomerang.h Bullet.h Camera.h CollisionGroup.h ContentManager.h Enemy.h Fireball.h GameConstants.h Geom.h Goomba.h Hammer.h HammerBro.h LayerController.h MapLayer.h ObjectHeaders.h ObjectLayer.h OneWayPlatform.h Player.h PlayerSpawn.h ProgressBar.h Projectile.h TestCollider.h Texture.h TileLayer.h Tileset.h TriggerArea.h WorldDebugger.h WorldIO.h WorldMap.h WorldObject.h FireMagic.h FireWizard.h EnemyBoundary.h ScreenManager.h MenuScreen.h MainMenuScreen.h Screen.h
FUNC1 = AnimatedTexture
FUNC2 = Block
FUNC3 = Boomerang
FUNC4 = Bullet
FUNC5 = Camera
FUNC6 = ContentManager
FUNC7 = Enemy
FUNC8 = Fireball
FUNC9 = Geom
FUNC10 = Goomba
FUNC11 = Hammer
FUNC12 = HammerBro
FUNC13 = LayerController
FUNC14 = MapLayer
FUNC15 = ObjectLayer
FUNC16 = OneWayPlatform
FUNC17 = Player
FUNC18 = PlayerSpawn
FUNC19 = ProgressBar
FUNC20 = Projectile
FUNC21 = TestCollider
FUNC22 = Texture
FUNC23 = TileLayer
FUNC24 = Tileset
FUNC25 = TriggerArea
FUNC26 = WorldDebugger
FUNC27 = WorldMap
FUNC28 = WorldObject
FUNC29 = FireWizard
FUNC30 = FireMagic
FUNC31 = EnemyBoundary
FUNC32 = ScreenManager
FUNC33 = MenuScreen
FUNC34 = MainMenuScreen
FUNC35 = Screen
EXEC = fc2proj
FLAGS = -O0 -g3 -lSDL2 -lSDL2_image -lSDL2main -std=c++11 -static-libstdc++ -lSDL2_ttf

all: $(EXEC)

$(EXEC): $(MAIN).o $(DOT_OS)
	$(CMP) $(MAIN).o $(DOT_OS) $(FLAGS) -o $(EXEC)

$(MAIN).o: $(MAIN).cpp $(HEADERS)
	$(CMP) $(FLAGS) -c $(MAIN).cpp

$(FUNC27).o: $(FUNC27).cpp
	$(CMP) $(FLAGS) -c $(FUNC27).cpp
$(FUNC1).o: $(FUNC1).cpp
	$(CMP) $(FLAGS) -c $(FUNC1).cpp

$(FUNC2).o: $(FUNC2).cpp
	$(CMP) $(FLAGS) -c $(FUNC2).cpp

$(FUNC3).o: $(FUNC3).cpp
	$(CMP) $(FLAGS) -c $(FUNC3).cpp

$(FUNC4).o: $(FUNC4).cpp
	$(CMP) $(FLAGS) -c $(FUNC4).cpp

$(FUNC5).o: $(FUNC5).cpp
	$(CMP) $(FLAGS) -c $(FUNC5).cpp

$(FUNC6).o: $(FUNC6).cpp
	$(CMP) $(FLAGS) -c $(FUNC6).cpp

$(FUNC7).o: $(FUNC7).cpp
	$(CMP) $(FLAGS) -c $(FUNC7).cpp

$(FUNC8).o: $(FUNC8).cpp
	$(CMP) $(FLAGS) -c $(FUNC8).cpp

$(FUNC9).o: $(FUNC9).cpp
	$(CMP) $(FLAGS) -c $(FUNC9).cpp

$(FUNC10).o: $(FUNC10).cpp
	$(CMP) $(FLAGS) -c $(FUNC10).cpp

$(FUNC11).o: $(FUNC11).cpp
	$(CMP) $(FLAGS) -c $(FUNC11).cpp

$(FUNC12).o: $(FUNC12).cpp
	$(CMP) $(FLAGS) -c $(FUNC12).cpp

$(FUNC29).o: $(FUNC29).cpp
	$(CMP) $(FLAGS) -c $(FUNC29).cpp

$(FUNC30).o: $(FUNC30).cpp
	$(CMP) $(FLAGS) -c $(FUNC30).cpp

$(FUNC13).o: $(FUNC13).cpp
	$(CMP) $(FLAGS) -c $(FUNC13).cpp

$(FUNC14).o: $(FUNC14).cpp
	$(CMP) $(FLAGS) -c $(FUNC14).cpp

$(FUNC15).o: $(FUNC15).cpp
	$(CMP) $(FLAGS) -c $(FUNC15).cpp

$(FUNC16).o: $(FUNC16).cpp
	$(CMP) $(FLAGS) -c $(FUNC16).cpp

$(FUNC17).o: $(FUNC17).cpp
	$(CMP) $(FLAGS) -c $(FUNC17).cpp

$(FUNC18).o: $(FUNC18).cpp
	$(CMP) $(FLAGS) -c $(FUNC18).cpp

$(FUNC19).o: $(FUNC19).cpp
	$(CMP) $(FLAGS) -c $(FUNC19).cpp

$(FUNC20).o: $(FUNC20).cpp
	$(CMP) $(FLAGS) -c $(FUNC20).cpp

$(FUNC21).o: $(FUNC21).cpp
	$(CMP) $(FLAGS) -c $(FUNC21).cpp

$(FUNC22).o: $(FUNC22).cpp
	$(CMP) $(FLAGS) -c $(FUNC22).cpp

$(FUNC23).o: $(FUNC23).cpp
	$(CMP) $(FLAGS) -c $(FUNC23).cpp

$(FUNC24).o: $(FUNC24).cpp
	$(CMP) $(FLAGS) -c $(FUNC24).cpp

$(FUNC25).o: $(FUNC25).cpp
	$(CMP) $(FLAGS) -c $(FUNC25).cpp

$(FUNC26).o: $(FUNC26).cpp
	$(CMP) $(FLAGS) -c $(FUNC26).cpp


$(FUNC28).o: $(FUNC28).cpp
	$(CMP) $(FLAGS) -c $(FUNC28).cpp

$(FUNC31).o: $(FUNC31).cpp
	$(CMP) $(FLAGS) -c $(FUNC31).cpp

$(FUNC32).o: $(FUNC32).cpp
	$(CMP) $(FLAGS) -c $(FUNC32).cpp
$(FUNC33).o: $(FUNC33).cpp
	$(CMP) $(FLAGS) -c $(FUNC33).cpp
$(FUNC34).o: $(FUNC34).cpp
	$(CMP) $(FLAGS) -c $(FUNC34).cpp
$(FUNC35).o: $(FUNC35).cpp
	$(CMP) $(FLAGS) -c $(FUNC35).cpp
clean:
	rm *.o $(EXEC) *~
