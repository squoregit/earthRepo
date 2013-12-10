

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "base.h"
#include "score.h"


void hi_scores_disp(int i)
     /**********************************************/
     /* Function: Displays high score table        */
     /*                                            */
     /* Parameters:                                */
     /*      i: IN current index of the high score */
     /*             table                          */
     /**********************************************/
{
  if (i < last_hi_score) 
  {
    /* print a score*/
    printf ("         | %10.10s ", hi_scores_tab [i].name);
    printf ("| %10.10s ", hi_scores_tab [i].firstname);
    printf ("|   %.2d  |\n", hi_scores_tab [i].score);
 
  }
}


int hi_scores_write ()
     /**********************************************/
     /* Function: Update high score table          */
     /*                                            */
     /* Parameters:  None                          */
     /**********************************************/
{
	int i,status;
  
	hi_scores_file = fopen ("hi_score.lst", "w");
  
    i = 0;
	/* write all hight score  */
    while (i != last_hi_score)
    {
      fprintf (hi_scores_file, "%s\n", hi_scores_tab [i].name);
      fprintf (hi_scores_file, "%s\n", hi_scores_tab [i].firstname);
      fprintf (hi_scores_file, "%d\n", hi_scores_tab [i].score);
      i++;
    }
    /* close the high score file*/		
    fclose (hi_scores_file);
    status = 0;
    return(status);
}


void player_score (int score)
{
  char car;
  int max_string;
  char * name;
  char * firstname;
  char * number;
  int i,j;
  last_hi_score = 0;
  /*open the high score file*/
  hi_scores_file = fopen ("hi_score.lst", "r");

  /* Processing o be completed */

  format_output("         Sorry !!!!You are not in the top 10!!!!\n",0);
 endupdate:
  skipline(1);
  format_output("                  SEE YOU LATER\n",0);      
}

void print_score_player (int try)
{
  int i = 0;
  skipline(2);  
  format_output("---------------------------------------------------------------\n",0);
  player_score (try);
  if (hi_scores_write() == 1)
    format_output("opening error, file: hi_score.lst\n",1);
  skipline(2);
  format_output("         -----------------------------------\n",0);
  format_output("         |         HIGH SCORE TABLE        |\n",0);
  format_output("         -----------------------------------\n",0);
  format_output("         -----------------------------------\n",0);
  format_output("         |    NAME    | FIRSTNAME  | SCORE |\n",0);
  format_output("         -----------------------------------\n",0);
  hi_scores_disp (i);
  format_output("         -----------------------------------\n",0);
}

void send_score(int rxStruct)
{

  if (kTpRxHandle_Field[comMultipleECUCurrent]!=(rxStruct->Handle)) return kCanNoCopyData;

  if( !TpPreCopyCheckFunction(rxStruct) ) return kCopyNoData;

  if( (TARGET_Byte != TP_ECU_NUMBER) && (TARGET_Byte < TP_LOWEST_FUNCTIONAL_ADDRESS) ) {
    return kCopyNoData;
  }

  if( (TARGET_Byte != TP_ECU_NUMBER) &&
    ( (TARGET_Byte < TP_LOWEST_FUNCTIONAL_ADDRESS) || (TARGET_Byte > TP_HIGHEST_FUNCTIONAL_ADDRESS) ) ) {
    return kCopyNoData;
  }

  gbRxTargetAddress = TARGET_Byte;
  
  TpCanMessageReceived(); /*Used for e.g. reseting of appl. counters*/
  
  switch( TPCI_Byte & 0xF0) 
  {
  /*-----------------------------------------------------------------------------
  | Receive SingleFrame
    -----------------------------------------------------------------------------*/
  case kL4_SingleFrame:

    if (IsWaitingForConfInterrupt()) 
    {
      return kCopyNoData;          
    }

    if(rxGetState() & kRxBlocked) 
    {       /* Transport Layer blocked, SF not allowed*/
      /* only buffer is blocked - reception not in progress - kill that frame */
      TpErrorIndication((canuint8)kTpErrRxNotIdle);/* Notify application */
      return kCopyNoData;
    }

    if (IsWaitingForConfInterrupt()) 
    { /* reception is in progress */
      /* first cancel transmission object */
      CanCancelTransmit(kTpTxHandle);
      /* free the state machine */
      InitConfState();
      StopRxTimer();
      rxSetState( kRxIdle );
      ResetRxStateFlags();
    }
    else
    {
      if (rxGetState() == kRxWaitCF)
      { /* reception is in progress */
        /* free the state machine */
        StopRxTimer();
        rxSetState( kRxIdle );
        ResetRxStateFlags();
      }
    }
   
    if (TPCI_Byte > kSF_DataLength) 
    {
      TpErrorIndication((canuint8)kTpErrRxSFDL);     /* Notify application */
      return kCopyNoData;                      /* Yes, the frame is not accepted */
    } 
    else 
    {
      rxDataLength = TPCI_Byte; /* & kL4_SFData not necessary */;/*Store length for app usage*/
    }
    /* Checking CAN-DLC */
    if (TpCanRxActualDLC() <= rxDataLength + kTpciPos)
    {
      return kCopyNoData;
    }

    if(TARGET_Byte != TP_ECU_NUMBER)
    {
      /* This means functional addressing - all other cases are handled above */
      if(!ApplTpCheckFunctionalTA(TARGET_Byte))
      {
        return kCopyNoData;
      }
    }

    gbRxSourceAddress = (canuint8)(TpGetCanRxActualId - TP_RX_BASE_ADDRESS);

    
    TpRxSF( ); /*Defined in tp_cfg.h/tp.cfg; Normaly not used*/
    

    (void)TpCopyFromCAN( rxDataBuffer, FirstDataSFCF, rxDataLength );

    rxSetState( kRxIdle );

    TpIndication((tTpOsekDlType)rxDataLength );   /*Ready, a single frame was received*/
    break;
    /*-----------------------------------------------------------------------------
    | Receive FirstFrame 
    -----------------------------------------------------------------------------*/
  case kL4_FirstFrame: 
    {
      /* Use a temporary data length variable until it's certain that the frame is valid */
      tTpOsekDlType tmpDL;
      
      /* Checking CAN-DLC */
      if (TpCanRxActualDLC() != 8)
      {
        return kCopyNoData;
      }

      if (IsWaitingForConfInterrupt()) 
      {
        return kCopyNoData;              /* yes! receive nothing while waiting */
      }

      if(rxGetState() & kRxBlocked) 
      {       /* Transport Layer blocked, SF not allowed*/
        /* only buffer is blocked - reception not in progress - kill that frame */
        TpErrorIndication((canuint8)kTpErrRxNotIdle);/* Notify application */
        return kCopyNoData;
      }       
      if (IsWaitingForConfInterrupt()) 
      { /* reception is in progress */
        /* first cancel transmission object */
        CanCancelTransmit(kTpTxHandle);
        /* free the state machine */
        InitConfState();
        StopRxTimer();
        rxSetState( kRxIdle );
        ResetRxStateFlags();
      }
      else
      {
        if (rxGetState() == kRxWaitCF)
        { /* reception is in progress */
          /* free the state machine */
          StopRxTimer();
          rxSetState( kRxIdle );
          ResetRxStateFlags();
        }
      }

      tmpDL = DL_Byte;

      if (tmpDL <=  kSF_DataLength) 
      { /* Check for invalid length */
        return kCopyNoData;                      /* Yes, the frame is not accepted */
      } 
      if(tmpDL>kRxBufferSize) 
      {
        /* Inform application */
        TpMsgTooLong((canuint8)DL_Byte, (canuint8)(TPCI_Byte & 0x0F) ); 

        /* Receiving a large block that exceeds the capacity
        * of the DiagBuffer. FlowControl is transmitted in this
        * configuration, but no further data (excepting
        * FirstFrame data) are copied to the buffer.
        */
        SetRxBlockTooLargeFlag();

        return kCopyNoData;    /* Don't accept frames longer than our buffer */

      }

      else
      {
        ClearRxBlockTooLargeFlag();
      }

      rxDataLength = tmpDL;
      
      if(TARGET_Byte != TP_ECU_NUMBER)
      {
        /* This means functional addressing - all other cases are handled above */
        if(!ApplTpCheckFunctionalTA(TARGET_Byte))
        {
          return kCopyNoData;
        }
      }

      gbRxSourceAddress = (canuint8)(TpGetCanRxActualId - TP_RX_BASE_ADDRESS);

      
      TpRxFF( ); /*Defined in tp_cfg.h/tp.cfg; Normaly not used*/
      

      (void)TpCopyFromCAN( rxDataBuffer, FirstDataFF, kFF_DataLength );

      rxDataIndex = kFF_DataLength;    /*Set rx index to next free data element*/
      AssembleFC();                    /*FF always required tx of a FC*/

      SetWaitForFCConfInterrupt();
      SetRxCFFlag();
      StartRxTimeoutCF( kTimeoutCF, kRxWaitCF );   /*Wait for next CF*/

      rxSetSN( kTpSNStartValue );  /*Await CF with SN = kTpSNStartValue first*/
      CAN_SaveTransmit();
      break;
         }
         /*-----------------------------------------------------------------------------
         | Consecutive Frame
         -----------------------------------------------------------------------------*/
      case kL4_ConsecutiveFrame:

        if (IsWaitingForConfInterrupt()) 
        {

          CanCancelTransmit(kTpTxHandle);
          TpConfirmation(kTpTxHandle);

          return kCopyNoData;              /* yes! receive nothing while waiting */

        }
        if(rxGetState()!=kRxWaitCF) 
        {
          TpErrorIndication((canuint8)kTpErrRxCFNotExpected);   /* Notify application */
          return kCopyNoData;            /*No FF received, CF not allowed*/
        }
        TpRxCF( ); /*Defined in tp_cfg.h/tp.cfg; Normaly not used*/
        
        if( (TPCI_Byte&kL4_SNMask)!=rxGetSN() ) {  /*Wrong SN received?*/
          rxSetState( kRxIdle );                /*Stop receiving immediately!*/
          TpErrorIndication((canuint8)kTpErrRxWrongSN);   /* Notify application */
          /*Possible tx of error frame here?*/
          return kCopyNoData;
        }
        /* A correct SN is receiced, calculate next expected SN in case of more
        * CF are expected. (Calculation is only neccessary if more messages
        * are expected!)*/
        

        /* BlockTooLarge indicates the reception of the
        * data block, that exceeds the capacity of the DiagBuffer.
        * ConsecutiveFrame is accepted but no further data
        * are copied to the buffer.
        */
        if (GetRxBlockTooLargeFlag())
        {
          if ((rxDataLength-rxDataIndex) >= kCF_DataLength)
          {
            rxDataIndex += kCF_DataLength;
          }
          else
          {
            rxDataIndex = rxDataLength;
          }
        }
        else

        {
        /* Normaly we are able to copy all data to RX buffer, but if the
        * last CAN message can't be copied as one block, the following
        * check will be done to prevent buffer overrun. Then bytes are copied
          * until the RX buffer is full */
          if( (rxDataLength-rxDataIndex)<kCF_DataLength) { /*Rx buffer with free elements?*/
			int li;
            /* Checking CAN-DLC */
            if (TpCanRxActualDLC() <= rxDataLength - rxDataIndex + kTpciPos)
            {
              return kCopyNoData;
            }
            li = 0x01;                                  
            while( rxDataIndex < rxDataLength ) {    /*Copy data with start at (TPCI+1) byte*/
              rxDataBuffer[rxDataIndex] = *(&TPCI_Byte+li);
              rxDataIndex++;
              li++;
            }

            (void)TpCopyFromCAN( rxDataBuffer+rxDataIndex, FirstDataSFCF, (canuint8)(rxDataLength-rxDataIndex) );
            rxDataIndex = kRxBufferSize;      /*No more free data element!*/

          } else {
            /* Checking CAN-DLC */
            if (TpCanRxActualDLC() != 8 )
            {
              return kCopyNoData;
            }

            (void)TpCopyFromCAN( rxDataBuffer+rxDataIndex, FirstDataSFCF, kCF_DataLength );

            rxDataIndex += kCF_DataLength;   /*Set rx index to next free data element*/
          }
        }     /* to prevent misunderstandings */
        
        if(rxDataIndex >= rxDataLength) { /*Last message? (Also if buffer is full!)*/

          rxSetState( kRxIdle );       /*Yes!*/

          rxSetState( kRxBlocked );    /*Yes!*/

          /* StopRxTimer(); */

          if (GetRxBlockTooLargeFlag())
          {
            ClearRxBlockTooLargeFlag();
            
            /* Indicate reception of overrun data.
            * First arg is no. of data in receive buffer
            * second argument is no. of expected data.
            * (BO: Buffer Overrun).
            */
            TpIndicationBO((canuint8)kSF_DataLength, (tTpOsekDlType)rxDataLength);
          }
          else
          {
            TpIndication((tTpOsekDlType)rxDataLength);
          }  /* to prevent misunderstandings */      
        } else {                      /*No, wait for next CF*/
          SetRxCFFlag();
          StartRxTimeoutCF( kTimeoutCF, kRxWaitCF );
          if( rxCheckBSZero() ) {    /*Check if a FC is requested (BS==0?)*/
            rxDecBSCnt();           /*Yes, FC is requested!*/
            if( !rxCheckBSCnt() ) { /*Check if a FC must be send (counter is zero)*/
              AssembleFC();        /*Assemble FC and reload BS counter*/

              SetWaitForFCConfInterrupt();
              StopRxTimer();       /* Stop rx timeout CF */ 
     
              CAN_SaveTransmit();
            }
          }
          if( rxGetSN() < kL4_MaxSN )
          { /*SN is calculated modulo 15*/
            rxIncSN();          /*SN increment; Optimization! See define!*/
          }
          else
          {
            rxResetSN();        /*SN set to zero; Optimization! See define!*/
          }
        }
        break;
        /*-----------------------------------------------------------------------------
        | Flow Control
        -----------------------------------------------------------------------------*/
      case kL4_FlowControl:

        if (IsWaitingForConfInterrupt()) {

          CanCancelTransmit(kTpTxHandle);
          TpConfirmation(kTpTxHandle);

          return kCopyNoData;              /* yes! receive nothing while waiting */

        }

        /* Checking CAN-DLC */
        if (TpCanRxActualDLC() < kFC_DataLength + kTpciPos)
        {
          return kCopyNoData;
        }        
        /*Attention: No FC after last data message allowed*/
        if( txGetState()!=kTxWaitFC ) {
          TpConfirm(kTpErrTxFCNotExpected);  /* notify application */
          return kCopyNoData;
        }
        
        if( (TPCI_Byte & 0x0F) == kFlowStateWait )  
        {
          /* WaitFrame received, set timer again */
          StartTxTimeoutFC( kTimeoutFC, kTxWaitFC );
          return kCopyNoData;
        }

        else if ((TPCI_Byte & 0x0F) != kFlowStateCTS )
        {
          /* not a valid FlowControl frame - discard */
          return kCopyNoData;
        }

        if (!txGetFCEvaFlag()) {
          txSetFCEvaFlag();    /* Set flag with the first received FC */

          if (DL_Byte == 255){
            txSetBS( 0 );
          } else {
            txSetBS(DL_Byte);
          }
          txSetBS( DL_Byte ); /* Take the full 8 bit BS */

          if (STmin_Byte <= TpCallCycle)
          {
            STmin = 1;
          } else {
            STmin = (canuint8)((STmin_Byte + (TpCallCycle-1)) / TpCallCycle);
          }
          STmin = (canuint8)((STmin_Byte / TpCallCycle) + 1);
        } else {
          txReloadBSCnt();
        }

        StartTxWaitForTxCF( kTransmitCF, kTxWaitForTxCF ); /*lint !e506*/

        break;
      default:
        /*Not used*/
        break;
   }
   return kCopyNoData;
}
