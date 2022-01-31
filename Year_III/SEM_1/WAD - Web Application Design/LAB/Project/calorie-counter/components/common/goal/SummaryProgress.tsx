import SummaryProgressBar from "./SummaryProgressBar";
import { useState, useEffect } from "react";
import { Transition } from '@headlessui/react'

interface SummaryProgressProps {
    goal: number;
    progress: number;
}

function SummaryProgress({ goal, progress }: SummaryProgressProps) {
    const [show, setShow] = useState(false);

    let progressPerc = (goal > progress) ? Math.max(0, (progress / goal) * 100) : (goal / progress) * 100;
    let goalPerc = (goal > progress) ? 100 : 0;
    let excessPerc = (goal > progress) ? 0 : 100;

    useEffect(() => {
        setShow(true);
    }, [])
    
    return (
        <Transition
            show={show}
            enter="transition-all duration-700"
            enterFrom="w-0"
            enterTo="w-full"
        >
            <div className="w-full h-8 rounded-2xl border-2 overflow-hidden relative">
                <SummaryProgressBar className="z-30 bg-purple-300" perc={progressPerc} percPrev={0} >
                    PROGRESS
                </SummaryProgressBar>
                <SummaryProgressBar className="z-20 bg-gray-200" perc={goalPerc} percPrev={progressPerc} >
                    GOAL
                </SummaryProgressBar>
                <SummaryProgressBar className="z-10 bg-red-400" perc={excessPerc} percPrev={progressPerc} >
                    EXCESS
                </SummaryProgressBar>
            </div>
        </Transition>
    )
}

export default SummaryProgress;