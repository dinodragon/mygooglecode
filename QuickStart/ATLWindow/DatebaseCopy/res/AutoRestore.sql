d e c l a r e   @ b k f i l e   v a r c h a r ( 2 0 0 )  
 s e t   @ b k f i l e   =   ' B K F I L E '  
 d e c l a r e   @ t a r g e t D b N a m e   v a r c h a r ( 2 0 0 )  
 s e t   @ t a r g e t D b N a m e   =   ' T A R G E T D B N A M E '  
  
 - -  Rd��s	gpenc�^ 
 E X E C   m s d b . d b o . s p _ d e l e t e _ d a t a b a s e _ b a c k u p h i s t o r y   @ d a t a b a s e _ n a m e   =   @ t a r g e t D b N a m e  
 U S E   [ m a s t e r ]  
 I F     E X I S T S   ( s e l e c t   *   f r o m   m a s t e r . . S y s D a t a b a s e s   w h e r e   n a m e   =   @ t a r g e t D b N a m e )  
 b e g i n  
 	 d e c l a r e   @ d r o p S q l   v a r c h a r ( 2 0 0 )  
 	 s e t   @ d r o p S q l   =   ' D R O P   D A T A B A S E   [ ' +   @ t a r g e t D b N a m e   + ' ] '  
 	 e x e c ( @ d r o p S q l )  
 e n d  
 - - ؞���vpenc�^_ 
 d e c l a r e   @ d e f a u l t P a t h   v a r c h a r ( 2 0 0 )  
 s e l e c t   @ d e f a u l t P a t h   =   ( s e l e c t   f i l e N a m e   f r o m   m a s t e r . . s y s d a t a b a s e s   w h e r e   n a m e = ' m a s t e r ' )  
 s e t   @ d e f a u l t P a t h   =   r e v e r s e ( @ d e f a u l t P a t h )  
 s e t   @ d e f a u l t P a t h = r e v e r s e ( s u b s t r i n g ( @ d e f a u l t P a t h , c h a r i n d e x ( ' \ ' , @ d e f a u l t P a t h ) , 2 6 0 ) )  
 s e l e c t   @ d e f a u l t P a t h  
  
 - - X[�P4N�e�e�N�Oo`h� 
 c r e a t e   t a b l e   # f i l e l i s t i n f o  
 (  
 	 L o g i c a l N a m e 	 n v a r c h a r ( 1 2 8 )   	 ,  
 	 P h y s i c a l N a m e 	 n v a r c h a r ( 2 6 0 )   	 ,  
 	 [ T y p e ] 	 c h a r ( 1 )   	 ,  
 	 F i l e G r o u p N a m e 	 n v a r c h a r ( 1 2 8 )   	 ,  
 	 S i z e 	 n u m e r i c ( 2 0 , 0 )   	 ,  
 	 M a x S i z e 	 n u m e r i c ( 2 0 , 0 )   	 ,  
 	 F i l e I D 	 b i g i n t   	 ,  
 	 C r e a t e L S N 	 n u m e r i c ( 2 5 , 0 )   	 ,  
 	 D r o p L S N 	 n u m e r i c ( 2 5 , 0 )   N U L L 	 ,  
 	 U n i q u e I D 	 u n i q u e i d e n t i f i e r   	 ,  
 	 R e a d O n l y L S N 	 n u m e r i c ( 2 5 , 0 )   N U L L   	 ,  
 	 R e a d W r i t e L S N 	 n u m e r i c ( 2 5 , 0 )   N U L L 	 ,  
 	 B a c k u p S i z e I n B y t e s 	 b i g i n t   	 ,  
 	 S o u r c e B l o c k S i z e 	 i n t   	 ,  
 	 F i l e G r o u p I D 	 i n t   	 ,  
 	 L o g G r o u p G U I D 	 u n i q u e i d e n t i f i e r   N U L L   	 ,  
 	 D i f f e r e n t i a l B a s e L S N 	 n u m e r i c ( 2 5 , 0 )   N U L L 	 ,  
 	 D i f f e r e n t i a l B a s e G U I D 	 u n i q u e i d e n t i f i e r   	 ,  
 	 I s R e a d O n l y 	 b i t   	 ,  
 	 I s P r e s e n t 	 b i t   	 ,  
 	 T D E T h u m b p r i n t 	 v a r b i n a r y ( 3 2 )  
 )  
 - - �NY�N�e�N-N���S;����e�N�Oo`��_0R@ m o v e S q l  
 d e c l a r e   @ s q l   v a r c h a r ( 2 0 0 )  
 s e t   @ s q l   =   ' r e s t o r e   f i l e l i s t o n l y   f r o m   d i s k = ' ' ' + @ b k f i l e + ' ' ' '  
 i n s e r t   i n t o   # f i l e l i s t i n f o   e x e c ( @ s q l )    
 s e l e c t   L o g i c a l N a m e , [ T y p e ]   f r o m   # f i l e l i s t i n f o    
 d e c l a r e   @ m o v e S q l   v a r c h a r ( 1 0 2 4 )  
 s e t   @ m o v e S q l   =   ' '  
 d e c l a r e   @ L o g i c a l N a m e   v a r c h a r ( 1 2 8 )  
 d e c l a r e   @ T y p e   c h a r ( 1 )  
 d e c l a r e   @ i n d e x   i n t  
 s e t   @ i n d e x = 0    
 d e c l a r e   # f   c u r s o r   f o r   s e l e c t   L o g i c a l N a m e , [ T y p e ]   f r o m   # f i l e l i s t i n f o    
 o p e n   # f    
 f e t c h   n e x t   f r o m   # f   i n t o   @ L o g i c a l N a m e , @ T y p e  
  
 w h i l e   @ @ f e t c h _ s t a t u s = 0  
 	 b e g i n    
 	 	 s e t   @ m o v e S q l = @ m o v e S q l + ' , m o v e   ' ' ' + @ L o g i c a l N a m e + ' ' '   t o   ' ' ' + @ d e f a u l t P a t h  
  
 + @ t a r g e t D b N a m e + c a s t ( @ i n d e x   a s   v a r c h a r )    
 	 	 +   c a s e   @ T y p e   w h e n   ' D '   t h e n   ' . m d f ' ' '   e l s e   ' . l d f ' ' '   e n d    
 	 	 s e t   @ i n d e x = @ i n d e x + 1    
 	 	 f e t c h   n e x t   f r o m   # f   i n t o   @ L o g i c a l N a m e , @ T y p e    
 	 e n d    
 c l o s e   # f    
 d e a l l o c a t e   # f    
 d r o p   t a b l e   # f i l e l i s t i n f o  
 p r i n t   @ m o v e S q l  
  
 - - ؏�Spenc�^ 
 d e c l a r e   @ r e s t o r e S q l   v a r c h a r ( 1 0 2 4 )  
 s e t   @ r e s t o r e S q l   =   ' r e s t o r e   d a t a b a s e   '   +   @ t a r g e t D b N a m e   +   '   f r o m   d i s k = ' ' '   +   @ b k f i l e   +   ' ' ' W I T H      
  
 F I L E   =   1 '   +   @ m o v e S q l  
 - - p r i n t   @ r e s t o r e S q l  
 e x e c ( @ r e s t o r e S q l )   