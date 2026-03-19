const exposes = require('zigbee-herdsman-converters/lib/exposes');
const e = exposes.presets;
const ea = exposes.access;

const fzGas = {
    cluster: 'seMetering',
    type: ['attributeReport', 'readResponse'],
    convert: (model, msg, publish, options, meta) => {
        if (msg.data['currentSummDelivered'] !== undefined) {
            const raw = msg.data['currentSummDelivered'];
            let rawValue;
            if (Array.isArray(raw)) {
                rawValue = raw[0] + raw[1] * 0x100000000;
            } else {
                rawValue = Number(raw);
            }
            const divisor = msg.data['divisor'] || 100;
            const multiplier = msg.data['multiplier'] || 1;
            return { gas: rawValue * multiplier / divisor };
        }
    },
};

const fzBattery = {
    cluster: 'genPowerCfg',
    type: ['attributeReport', 'readResponse'],
    convert: (model, msg, publish, options, meta) => {
        const result = {};
        if (msg.data['batteryPercentageRemaining'] !== undefined) {
            result.battery = Math.round(msg.data['batteryPercentageRemaining'] / 2);
        }
        if (msg.data['batteryVoltage'] !== undefined) {
            result.battery_voltage = msg.data['batteryVoltage'] / 10;
        }
        if (Object.keys(result).length > 0) return result;
    },
};

const definition = {
    zigbeeModel: ['MiCASAGasCounter'],
    model: 'MiCASAGasCounter',
    vendor: 'Custom devices (DiY)',
    description: 'Zigbee Gas counter',
    fromZigbee: [fzGas, fzBattery],
    toZigbee: [],
    exposes: [
        e.numeric('gas', ea.STATE).withUnit('m³').withDescription('Total gas consumption'),
        e.battery(),
        e.numeric('battery_voltage', ea.STATE).withUnit('V').withDescription('Battery voltage'),
    ],
    configure: async (device, coordinatorEndpoint) => {
        const endpoint = device.getEndpoint(1);
        await endpoint.read('seMetering', ['multiplier', 'divisor']);
        await endpoint.bind('seMetering', coordinatorEndpoint);
        await endpoint.configureReporting('seMetering', [{
            attribute: 'currentSummDelivered',
            minimumReportInterval: 10,
            maximumReportInterval: 65000,
            reportableChange: 10,
        }]);
        await endpoint.read('genPowerCfg', ['batteryVoltage', 'batteryPercentageRemaining']);
    },
    onEvent: async (type, data, device) => {
        if (type === 'deviceAnnounce' || type === 'deviceJoined') {
            const endpoint = device.getEndpoint(1);
            try {
                await endpoint.read('genPowerCfg', ['batteryVoltage', 'batteryPercentageRemaining']);
            } catch (e) {}
        }
    },
};

module.exports = definition;