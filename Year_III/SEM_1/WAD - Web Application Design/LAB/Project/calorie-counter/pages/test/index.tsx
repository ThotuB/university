import Loading from "components/common/Loading";
import TextField from "../../components/common/TextField";
import Pagination from "components/common/Pagination";

import { useState, useEffect } from "react";
import React from "react";
import ToggleSwitch from "components/common/ToggleSwitch";

export default function Index() {

    return (
        <div className="flex justify-center p-2">
            <ToggleSwitch />
        </div>

    );
}