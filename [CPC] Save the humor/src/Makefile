SUBDIR=game
GAMEFILE=game.dsk

all: game
	@echo "&&&&&&&&&&&&&"
	@echo "&&& Copying your game from $(SUBDIR)/$(GAMEFILE) to here"
	@echo "&&&&&&&&&&&&&"
	@cp $(SUBDIR)/$(GAMEFILE) .
	
game: force
	@echo "&&&&&&&&&&&&&"
	@echo "&&& Entering $(SUBDIR) and compiling your project"
	@echo "&&&&&&&&&&&&&"
	@cd $(SUBDIR); $(MAKE) dsk

clean: force
	@echo "&&&&&&&&&&&&&"
	@echo "&&& Entering $(SUBDIR) and cleaning"
	@echo "&&&&&&&&&&&&&"
	@cd $(SUBDIR); $(MAKE) clean
	
force:
	@true
